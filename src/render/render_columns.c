/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_columns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:08:10 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	render_floor(int x, t_column_data *data)
{
	int			y;
	int			floor_end;
	uint32_t	color;

	y = data->draw_end + 1;
	floor_end = data->height;
	color = g_cache.floor_color;
	while (y < floor_end - 3)
	{
		data->pixels[y * data->width + x] = color;
		data->pixels[(y + 1) * data->width + x] = color;
		data->pixels[(y + 2) * data->width + x] = color;
		data->pixels[(y + 3) * data->width + x] = color;
		y += 4;
	}
	while (y < floor_end)
	{
		data->pixels[y * data->width + x] = color;
		y++;
	}
}

void	render_wall(int x, t_column_data *data)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = data->draw_start;
	while (y <= data->draw_end)
	{
		tex_y = (int)data->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= data->tex->height)
			tex_y = data->tex->height - 1;
		data->tex_pos += data->step;
		color = get_texture_pixel(data->tex, data->tex_x, tex_y);
		data->pixels[y * data->width + x] = color;
		y++;
	}
}

void	render_ceiling(int x, t_column_data *data)
{
	int			y;
	int			ceil_end;
	uint32_t	color;

	y = 0;
	ceil_end = data->draw_start;
	color = g_cache.ceil_color;
	while (y < ceil_end - 3)
	{
		data->pixels[y * data->width + x] = color;
		data->pixels[(y + 1) * data->width + x] = color;
		data->pixels[(y + 2) * data->width + x] = color;
		data->pixels[(y + 3) * data->width + x] = color;
		y += 4;
	}
	while (y < ceil_end)
	{
		data->pixels[y * data->width + x] = color;
		y++;
	}
}

void	draw_column_textured(t_game *game, t_ray *ray, int x)
{
	t_column_data	data;

	setup_column_data(game, ray, &data);
	render_ceiling(x, &data);
	render_wall(x, &data);
	render_floor(x, &data);
}
