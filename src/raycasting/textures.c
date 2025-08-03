/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/07/26 09:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

mlx_texture_t	*load_texture(const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		fprintf(stderr, "Failed to load texture: %s\n", path);
		exit(1);
	}
	return (texture);
}

int	load_textures(t_cube *cube)
{
	cube->tex_north = mlx_load_png(cube->data->textures[TEX_NO]);
	if (!cube->tex_north)
	{
		if (write(2, "Error: no s'ha pogut carregar la textura NO\n", 44) == -1)
			perror("write error");
		return (1);
	}
	cube->tex_south = mlx_load_png(cube->data->textures[TEX_SO]);
	if (!cube->tex_south)
	{
		if (write(2, "Error: no s'ha pogut carregar la textura SO\n", 44) == -1)
			perror("write error");
		return (1);
	}

	cube->tex_west = mlx_load_png(cube->data->textures[TEX_WE]);
	{
		if (write(2, "Error: no s'ha pogut carregar la textura WE\n", 44) == -1)
			perror("write error");
		return (1);
	}

	cube->tex_east = mlx_load_png(cube->data->textures[TEX_EA]);
	if (!cube->tex_east)
	{
		if (write(2, "Error: no s'ha pogut carregar la textura EA\n", 44) == -1)
			perror("write error");
		return (1);
	}

	return (0);
}

// void	load_textures_to_cube(t_cube *cube)
// {
// 	cube->tex_north = mlx_load_png("textures/wall_north.png");
// 	cube->tex_south = mlx_load_png("textures/wall_south.png");
// 	cube->tex_west = mlx_load_png("textures/wall_west.png");
// 	cube->tex_east = mlx_load_png("textures/wall_east.png");
// 	if (!cube->tex_north || !cube->tex_south || !cube->tex_west || !cube->tex_east)
// 	{
// 		write(2, "Error carregant textures\n", 26);
// 		exit(1);
// 	}
// }

