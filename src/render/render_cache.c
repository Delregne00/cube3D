/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 render_cache.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:57:28 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:57:28 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "includes/cube.h"

static uint32_t	rgb_to_color(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

static void	cache_init_render(t_game *game)
{
	t_cube	*cube;

	if (!game || !game->cube)
		return ;
	cube = game->cube;
	game->cache.floor_color = rgb_to_color(cube->data->f_color[0],
			cube->data->f_color[1], cube->data->f_color[2]);
	game->cache.ceil_color = rgb_to_color(cube->data->c_color[0],
			cube->data->c_color[1], cube->data->c_color[2]);
	game->cache.tex_cache[0] = &cube->tex_north;
	game->cache.tex_cache[1] = &cube->tex_south;
	game->cache.tex_cache[2] = &cube->tex_west;
	game->cache.tex_cache[3] = &cube->tex_east;
	game->cache.initialized = 1;
}

void	cache_init(t_game *game)
{
	if (!game->cache.initialized)
		cache_init_render(game);
}
