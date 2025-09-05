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

void	draw_player_direction(t_game *game)
{
	t_line_data	line_data;
	int			start_x;
	int			start_y;

	start_x = MINIMAP_OFFSET_X + (game->player.x * MINIMAP_SCALE);
	start_y = MINIMAP_OFFSET_Y + (game->player.y * MINIMAP_SCALE);
	line_data.x0 = start_x;
	line_data.y0 = start_y;
	line_data.x1 = start_x + (game->player.dir_x * PLAYER_DIR_LENGTH);
	line_data.y1 = start_y + (game->player.dir_y * PLAYER_DIR_LENGTH);
	line_data.color = COLOR_DIR;
	draw_line(game, &line_data);
}

void	draw_player(t_game *game)
{
	t_square_params	square_data;
	int				pixel_x;
	int				pixel_y;

	pixel_x = MINIMAP_OFFSET_X + (game->player.x * MINIMAP_SCALE);
	pixel_y = MINIMAP_OFFSET_Y + (game->player.y * MINIMAP_SCALE);
	square_data.size = PLAYER_SIZE;
	square_data.color = COLOR_PLAYER;
	draw_square(game, pixel_x - PLAYER_SIZE / 2, pixel_y - PLAYER_SIZE / 2,
		&square_data);
}

void	minimap_render(t_game *game)
{
	if (!game || !game->cube || !game->cube->map)
		return ;
	draw_map_grid(game);
	draw_player(game);
	draw_player_direction(game);
}
