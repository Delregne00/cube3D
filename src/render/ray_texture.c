/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:04:23 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static bool	is_valid_texture_coord(t_texture *tex, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= tex->width)
		return (false);
	if (tex_y < 0 || tex_y >= tex->height)
		return (false);
	return (true);
}

uint32_t	texture_pixel_get(t_texture *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (!tex || !tex->addr)
		return (0xFF00FF);
	if (!is_valid_texture_coord(tex, tex_x, tex_y))
		return (0xFF00FF);
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(uint32_t *)pixel);
}

static t_texture	*texture_vertical_select(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
		return (g_cache.tex_cache[2]);
	else
		return (g_cache.tex_cache[3]);
}

static t_texture	*texture_horizontal_select(t_ray *ray)
{
	if (ray->ray_dir_y < 0)
		return (g_cache.tex_cache[0]);
	else
		return (g_cache.tex_cache[1]);
}

t_texture	*texture_select(t_game *game, t_ray *ray)
{
	(void)game;
	if (ray->side == 0)
		return (texture_vertical_select(ray));
	else
		return (texture_horizontal_select(ray));
}
