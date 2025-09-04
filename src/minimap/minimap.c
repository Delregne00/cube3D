/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + j >= 0 && x + j < WIN_W && y + i >= 0 && y + i < WIN_H)
				put_pixel_to_image(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_direction(t_game *game)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = MINIMAP_OFFSET_X + (game->player.x * MINIMAP_SCALE);
	start_y = MINIMAP_OFFSET_Y + (game->player.y * MINIMAP_SCALE);
	end_x = start_x + (game->player.dir_x * PLAYER_DIR_LENGTH);
	end_y = start_y + (game->player.dir_y * PLAYER_DIR_LENGTH);
	draw_line(game, start_x, start_y, end_x, end_y, COLOR_DIR);
}

void	draw_player(t_game *game)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = MINIMAP_OFFSET_X + (game->player.x * MINIMAP_SCALE);
	pixel_y = MINIMAP_OFFSET_Y + (game->player.y * MINIMAP_SCALE);
	draw_square(game, pixel_x - PLAYER_SIZE / 2, pixel_y - PLAYER_SIZE / 2,
		PLAYER_SIZE, COLOR_PLAYER);
}

void	draw_map_grid(t_game *game)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	while (i < game->cube->map->filas)
	{
		j = 0;
		while (j < game->cube->map->max_columnas && game->cube->map->map[i][j])
		{
			pixel_x = MINIMAP_OFFSET_X + (j * MINIMAP_SCALE);
			pixel_y = MINIMAP_OFFSET_Y + (i * MINIMAP_SCALE);
			if (game->cube->map->map[i][j] == '1')
				draw_square(game, pixel_x, pixel_y, MINIMAP_SCALE, COLOR_WALL);
			else if (game->cube->map->map[i][j] == '0')
				draw_square(game, pixel_x, pixel_y, MINIMAP_SCALE, COLOR_FLOOR);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	if (!game || !game->cube || !game->cube->map)
		return ;
	draw_map_grid(game);
	draw_player(game);
	draw_player_direction(game);
}
