/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/04 21:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	init_line_params(t_line_params *params,
	int x0, int y0, int x1, int y1)
{
	params->dx = abs(x1 - x0);
	params->dy = abs(y1 - y0);
	if (x0 < x1)
		params->sx = 1;
	else
		params->sx = -1;
	if (y0 < y1)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx - params->dy;
}

static void	bresenham_step(t_line_params *params, int *x0, int *y0)
{
	int	e2;

	e2 = 2 * params->err;
	if (e2 > -params->dy)
	{
		params->err -= params->dy;
		*x0 += params->sx;
	}
	if (e2 < params->dx)
	{
		params->err += params->dx;
		*y0 += params->sy;
	}
}

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	t_line_params	params;
	int				current_x;
	int				current_y;
	int				target_x;
	int				target_y;

	current_x = x0;
	current_y = y0;
	target_x = x1;
	target_y = y1;
	init_line_params(&params, x0, y0, x1, y1);
	while (1)
	{
		if (current_x >= 0 && current_x < WIN_W
			&& current_y >= 0 && current_y < WIN_H)
			put_pixel_to_image(game, current_x, current_y, color);
		if (current_x == target_x && current_y == target_y)
			break ;
		bresenham_step(&params, &current_x, &current_y);
	}
}
