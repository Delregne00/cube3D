/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/02 18:10:25 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int	tex_pixel_get(t_texture *tex, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static	void texture_load(void *mlx, t_texture *tex, const char *path,
						 t_collector **collector)
{
	int	w;
	int	h;

	if (!mlx || !path)
		exit_program(collector, "Error: mlx NULL o path NULL", EXIT_FAILURE, mlx);
	tex->img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!tex->img)
		exit_program(collector, "Error carregant textura", EXIT_FAILURE, mlx);
	collector_append(collector, tex->img, RES_IMG, mlx);
	tex->addr = mlx_get_data_addr(tex->img,
								  &tex->bpp,
								  &tex->line_len,
								  &tex->endian);
	tex->width = w;
	tex->height = h;
	if (!tex->addr)
		exit_program(collector, "Error obtenint addr de textura", EXIT_FAILURE, mlx);
}

int	textures_load(t_game *game, t_collector **collector)
{
	t_cube *cube;

	cube = game->cube;
	texture_load(game->mlx, &cube->tex_north, cube->data->textures[0], collector);
	texture_load(game->mlx, &cube->tex_south, cube->data->textures[1], collector);
	texture_load(game->mlx, &cube->tex_west, cube->data->textures[2], collector);
	texture_load(game->mlx, &cube->tex_east, cube->data->textures[3], collector);
	printf("Textures carregades OK\n");
	return (0);
}
