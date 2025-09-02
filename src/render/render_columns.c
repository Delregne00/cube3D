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

void	draw_column_textured(t_game *game, t_ray *ray, int x)
{
	t_column_data	data;

	setup_column_data(game, ray, &data);
	render_ceiling(x, &data);
	render_wall(x, &data);
	render_floor(x, &data);
}

void	setup_column_data(t_game *game, t_ray *ray, t_column_data *data)
{
	data->tex = select_texture(game, ray);
	data->pixels = (uint32_t *)game->addr;
	data->width = game->width;
	data->height = game->height;
	data->draw_start = ray->drawStart;
	data->draw_end = ray->drawEnd;
	calc_texture_coordinates(game, ray, data);
}

void	calc_texture_coordinates(t_game *game, t_ray *ray, t_column_data *data)
{
	double	wallX;

	if (ray->side == 0)
		wallX = game->player.y + ray->perpWallDist * ray->rayDirY;
	else
		wallX = game->player.x + ray->perpWallDist * ray->rayDirX;
	wallX -= floor(wallX);
	data->texX = (int)(wallX * (double)data->tex->width);
	adjust_texture_x(ray, data);
	data->step = 1.0 * data->tex->height / ray->lineHeight;
	data->texPos = (ray->drawStart - data->height / 2.0 +
					ray->lineHeight / 2.0) *
				   data->step;
}

void	adjust_texture_x(t_ray *ray, t_column_data *data)
{
	if ((ray->side == 0 && ray->rayDirX > 0) ||
		(ray->side == 1 && ray->rayDirY < 0))
		data->texX = data->tex->width - data->texX - 1;
	if (data->texX < 0)
		data->texX = 0;
	if (data->texX >= data->tex->width)
		data->texX = data->tex->width - 1;
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

void	render_wall(int x, t_column_data *data)
{
	int			y;
	int			texY;
	uint32_t	color;

	y = data->draw_start;
	while (y <= data->draw_end)
	{
		texY = (int)data->texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= data->tex->height)
			texY = data->tex->height - 1;
		data->texPos += data->step;
		color = get_texture_pixel(data->tex, data->texX, texY);
		data->pixels[y * data->width + x] = color;
		y++;
	}
}

void	render_floor(int x, t_column_data *data)
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
