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

#include "MLX42/MLX42.h"
#include <string.h> // ft_strlen, strrchr

static mlx_texture_t	*load_texture(const char *path)
{
	const char	*ext;

	if (!path)
		return (NULL);
	ext = strrchr(path, '.');
	if (!ext)
		return (NULL);
	if (strcmp(ext, ".png") == 0)
		return mlx_load_png(path);
	// else if (strcmp(ext, ".xpm") == 0 || strcmp(ext, ".xpm42") == 0)
	// 	return mlx_load_xpm42(path);
	// else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
	// 	return mlx_load_png(path); // MLX42 no té suport natiu per JPEG, cal convertir prèviament a PNG o usar una lib externa
	else
		return NULL;
}

int	load_textures(t_cube *cube)
{
	cube->tex_north = load_texture(cube->data->textures[0]);
	if (!cube->tex_north)
		return (print_msg("Error: no s'ha pogut carregar la textura NO"), 1);

	cube->tex_south = load_texture(cube->data->textures[1]);
	if (!cube->tex_south)
		return (print_msg("Error: no s'ha pogut carregar la textura SO"), 1);

	cube->tex_west = load_texture(cube->data->textures[2]);
	if (!cube->tex_west)
		return (print_msg("Error: no s'ha pogut carregar la textura WE"), 1);

	cube->tex_east = load_texture(cube->data->textures[3]);
	if (!cube->tex_east)
		return (print_msg("Error: no s'ha pogut carregar la textura EA"), 1);

	return (0);
}
