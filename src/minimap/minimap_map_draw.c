/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_map_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/05 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	map_cell_draw(t_game *game, int i, int j)
{
	t_square_params	square_data;
	int				pixel_x;
	int				pixel_y;
	char			cell_type;

	pixel_x = MINIMAP_OFFSET_X + (j * MINIMAP_SCALE);
	pixel_y = MINIMAP_OFFSET_Y + (i * MINIMAP_SCALE);
	cell_type = game->cube->map->map[i][j];
	square_data.size = MINIMAP_SCALE;
	if (cell_type == '1')
	{
		square_data.color = COLOR_WALL;
		square_draw(game, pixel_x, pixel_y, &square_data);
	}
	else if (cell_type == '0')
	{
		square_data.color = COLOR_FLOOR;
		square_draw(game, pixel_x, pixel_y, &square_data);
	}
}

static void	map_row_draw(t_game *game, int i)
{
	int	j;

	j = 0;
	while (j < game->cube->map->max_columnas && game->cube->map->map[i][j])
	{
		map_cell_draw(game, i, j);
		j++;
	}
}

void	map_grid_draw(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->cube->map->filas)
	{
		map_row_draw(game, i);
		i++;
	}
}
