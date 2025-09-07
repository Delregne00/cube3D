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
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
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
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	data->tex_x = (int)(wall_x * (double)data->tex->width);
	adjust_texture_x(ray, data);
	data->step = 1.0 * data->tex->height / ray->line_height;
	data->tex_pos = (ray->draw_start - data->height / 2.0
			+ ray->line_height / 2.0) * data->step;
}

void	column_data_setup(t_game *game, t_ray *ray, t_column_data *data)
{
	data->tex = texture_select(game, ray);
	data->pixels = (uint32_t *)game->addr;
	data->width = game->width;
	data->height = game->height;
	data->draw_start = ray->draw_start;
	data->draw_end = ray->draw_end;
	calc_texture_coordinates(game, ray, data);
}
