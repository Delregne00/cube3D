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

mlx_image_t	*load_image(mlx_t *mlx, const char *path)
{
	const char		*ext;
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	if (!mlx || !path)
		return (NULL);
	// Verificar que el archivo existe
	if (access(path, F_OK) != 0)
	{
		printf("Error: no existe el archivo '%s'\n", path);
		return (NULL);
	}
	printf("load_image - path: %s\n", path);
	ext = strrchr(path, '.');
	if (!ext)
		return (NULL);
	// --- PNG ---
	if (strcmp(ext, ".png") == 0)
	{
		tex = mlx_load_png(path);
		if (!tex)
			return (NULL);
		img = mlx_texture_to_image(mlx, tex);
		mlx_delete_texture(tex);
		return (img);
	}
	// --- XPM / XPM42 ---
	else if (strcmp(ext, ".xpm") == 0 || strcmp(ext, ".xpm42") == 0)
	{
		printf("load_image es xpm\n");
		xpm_t *xpm = mlx_load_xpm42(path);
		if (!xpm)
			return (NULL);
		printf("load_image 2\n");
		img = mlx_texture_to_image(mlx, &xpm->texture);
		printf("load_image 3\n");
		mlx_delete_xpm42(xpm);
		printf("load_image 4\n");
		return (img);
	}
	return (NULL);
}

int load_textures(t_game *game, t_collector **collector)
{
    t_cube *cube = game->cube;

    cube->tex_north = load_image(game->mlx, cube->data->textures[0]);
    if (!cube->tex_north)
        exit_program(collector, "Error: textura NULL NO", EXIT_FAILURE);
    cube->tex_south = load_image(game->mlx, cube->data->textures[1]);
    if (!cube->tex_south)
        exit_program(collector, "Error: textura NULL SO", EXIT_FAILURE);
    cube->tex_west = load_image(game->mlx, cube->data->textures[2]);
    if (!cube->tex_west)
        exit_program(collector, "Error: textura NULL WE", EXIT_FAILURE);
    cube->tex_east = load_image(game->mlx, cube->data->textures[3]);
    if (!cube->tex_east)
        exit_program(collector, "Error: textura NULL EA", EXIT_FAILURE);
    printf("textures carregades OK\n");
    return (0);
}

//// versio q falla intentant usar textures .xpm
// static mlx_texture_t *load_texture(const char *path)
// {
//     const char *ext;

//     if (!path)
//         return (NULL);
//     printf("load_texture - path: %s\n", path);
//     ext = strrchr(path, '.');
//     if (!ext)
//         return (NULL);

//     if (strcmp(ext, ".png") == 0)
//     {
//         return (mlx_load_png(path));
//     }
//     else if (strcmp(ext, ".xpm") == 0 || strcmp(ext, ".xpm42") == 0)
//     {
//         xpm_t *xpm = mlx_load_xpm42(path);
//         if (!xpm)
//             return NULL;
//         mlx_texture_t *tex = mlx_texture_from_xpm42(xpm);
//         mlx_delete_xpm42(xpm); // Liberar el xpm_t después de extraer la textura
//         return tex;
//     }
//     else
//     {
//         return (NULL);
//     }
// }

// int	load_textures(t_cube *cube)
// {
// 	cube->tex_north = load_texture(cube->data->textures[0]);
// 	if (!cube->tex_north)
// 		return (print_msg("Error: no s'ha pogut carregar la textura NO"), 1);
// 	cube->tex_south = load_texture(cube->data->textures[1]);
// 	if (!cube->tex_south)
// 		return (print_msg("Error: no s'ha pogut carregar la textura SO"), 1);
// 	cube->tex_west = load_texture(cube->data->textures[2]);
// 	if (!cube->tex_west)
// 		return (print_msg("Error: no s'ha pogut carregar la textura WE"), 1);
// 	cube->tex_east = load_texture(cube->data->textures[3]);
// 	if (!cube->tex_east)
// 		return (print_msg("Error: no s'ha pogut carregar la textura EA"), 1);
// 	printf("textures carregades OK\n");
// 	return (0);
// }


//// versio q funciona OK pero usant textures en lloc de images
// static mlx_texture_t	*load_texture(const char *path)
// {
// 	const char	*ext;

// 	if (!path)
// 		return (NULL);
// 	printf("load_texture - path: %s\n", path);
// 	ext = strrchr(path, '.');
// 	if (!ext)
// 		return (NULL);
// 	if (strcmp(ext, ".png") == 0)
// 		return mlx_load_png(path);
// 	// else if (strcmp(ext, ".xpm") == 0 || strcmp(ext, ".xpm42") == 0)
// 	//	return mlx_load_xpm42(path);
// 	// else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
// 	// 	return mlx_load_png(path); // MLX42 no té suport natiu per JPEG, cal convertir prèviament a PNG o usar una lib externa
// 	else
// 		return (NULL);
// }
