/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_line_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/04 21:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

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

static void	init_line_params(t_line_params *params, t_line_data *data)
{
	params->dx = abs(data->x1 - data->x0);
	params->dy = abs(data->y1 - data->y0);
	if (data->x0 < data->x1)
		params->sx = 1;
	else
		params->sx = -1;
	if (data->y0 < data->y1)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx - params->dy;
}

void	line_draw(t_game *game, t_line_data *line_data)
{
	t_line_params	params;
	int				current_x;
	int				current_y;
	int				target_x;
	int				target_y;

	current_x = line_data->x0;
	current_y = line_data->y0;
	target_x = line_data->x1;
	target_y = line_data->y1;
	init_line_params(&params, line_data);
	while (1)
	{
		if (current_x >= 0 && current_x < WIN_W
			&& current_y >= 0 && current_y < WIN_H)
			put_pixel_to_image(game, current_x, current_y, line_data->color);
		if (current_x == target_x && current_y == target_y)
			break ;
		bresenham_step(&params, &current_x, &current_y);
	}
}
