/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/05 20:30:00 by jsayerza         ###   ########.fr       */
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

static void	draw_square_row(t_game *game, t_square_params *params, int row)
{
	int	j;
	int	pixel_x;
	int	pixel_y;

	j = 0;
	pixel_y = params->y + row;
	while (j < params->size)
	{
		pixel_x = params->x + j;
		if (pixel_x >= 0 && pixel_x < WIN_W && pixel_y >= 0 && pixel_y < WIN_H)
			put_pixel_to_image(game, pixel_x, pixel_y, params->color);
		j++;
	}
}

void	draw_square(t_game *game, int x, int y, t_square_params *square_data)
{
	t_square_params	params;
	int				i;

	params.x = x;
	params.y = y;
	params.size = square_data->size;
	params.color = square_data->color;
	i = 0;
	while (i < params.size)
	{
		draw_square_row(game, &params, i);
		i++;
	}
}
