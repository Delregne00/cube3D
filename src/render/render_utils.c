/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:09:04 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void init_render_cache(t_game *game)
{
	t_cube *cube;

	if (!game || !game->cube)
		return;
	cube = game->cube;
	g_cache.floor_color = rgb_to_color(cube->data->f_color[0],
									   cube->data->f_color[1],
									   cube->data->f_color[2]);
	g_cache.ceil_color = rgb_to_color(cube->data->c_color[0],
									  cube->data->c_color[1],
									  cube->data->c_color[2]);
	g_cache.tex_cache[0] = &cube->tex_north; // North
	g_cache.tex_cache[1] = &cube->tex_south; // South
	g_cache.tex_cache[2] = &cube->tex_west;	 // West
	g_cache.tex_cache[3] = &cube->tex_east;	 // East
	g_cache.initialized = 1;
}

uint32_t rgb_to_color(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void put_pixel_safe(t_game *game, int x, int y, uint32_t color)
{
	char *dst;

	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(uint32_t *)dst = color;
}

bool is_wall_fast(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return true;
	if (map_y >= game->cube->map->filas || map_x >= game->cube->map->max_columnas)
		return true;
	return (game->cube->map->map[map_y][map_x] == '1');
}
