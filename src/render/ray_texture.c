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

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	(void)game;
	if (ray->side == 0)
		return (select_vertical_texture(ray));
	else
		return (select_horizontal_texture(ray));
}

t_texture	*select_vertical_texture(t_ray *ray)
{
	if (ray->rayDirX < 0)
		return (g_cache.tex_cache[2]);
	else
		return (g_cache.tex_cache[3]);
}

t_texture	*select_horizontal_texture(t_ray *ray)
{
	if (ray->rayDirY < 0)
		return (g_cache.tex_cache[0]);
	else
		return (g_cache.tex_cache[1]);
}

uint32_t	get_texture_pixel(t_texture *tex, int texX, int texY)
{
	char	*pixel;

	if (!tex || !tex->addr)
		return (0xFF00FF);
	if (!is_valid_texture_coord(tex, texX, texY))
		return (0xFF00FF);
	pixel = tex->addr + (texY * tex->line_len + texX * (tex->bpp / 8));
	return (*(uint32_t *)pixel);
}

bool	is_valid_texture_coord(t_texture *tex, int texX, int texY)
{
	if (texX < 0 || texX >= tex->width)
		return (false);
	if (texY < 0 || texY >= tex->height)
		return (false);
	return (true);
}
