/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_columns_setup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 09:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/06 09:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	adjust_texture_x(t_ray *ray, t_column_data *data)
{
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		data->tex_x = data->tex->width - data->tex_x - 1;
	if (data->tex_x < 0)
		data->tex_x = 0;
	if (data->tex_x >= data->tex->width)
		data->tex_x = data->tex->width - 1;
}

static void	calc_texture_coordinates(t_game *game, t_ray *ray,
	t_column_data *data)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perpWallDist * ray->rayDirY;
	else
		wall_x = game->player.x + ray->perpWallDist * ray->rayDirX;
	wall_x -= floor(wall_x);
	data->tex_x = (int)(wall_x * (double)data->tex->width);
	adjust_texture_x(ray, data);
	data->step = 1.0 * data->tex->height / ray->lineHeight;
	data->tex_pos = (ray->drawStart - data->height / 2.0
			+ ray->lineHeight / 2.0) * data->step;
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
