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

// obtenir el color d’un píxel d’una textura <-- (raycasting, accés al píxel)
int	tex_pixel_get(t_texture *tex, int x, int y)
{
    char    *pixel;
    int     color;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0); // negre o transparent

    pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

static void	texture_load(void *mlx, t_texture *tex, const char *path,
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

// // Dibuixa la textura sencera a la finestra en la posició (ox, oy)
// static void texture_draw_test(t_game *game, t_texture *tex, int ox, int oy)
// {
//     int x, y;
//     int color;

//     y = 0;
//     while (y < tex->height && y + oy < game->height)
//     {
//         x = 0;
//         while (x < tex->width && x + ox < game->width)
//         {
//             color = tex_pixel_get(tex, x, y);
//             // dibuixar píxel a la imatge principal
//             char *dst = game->addr
//                 + ((y + oy) * game->line_length + (x + ox) * (game->bits_per_pixel / 8));
//             *(unsigned int *)dst = color;
//             x++;
//         }
//         y++;
//     }
// }

int	textures_load(t_game *game, t_collector **collector)
{
    t_cube	*cube;

    cube = game->cube;
    texture_load(game->mlx, &cube->tex_north, cube->data->textures[0], collector);
    texture_load(game->mlx, &cube->tex_south, cube->data->textures[1], collector);
    texture_load(game->mlx, &cube->tex_west,  cube->data->textures[2], collector);
    texture_load(game->mlx, &cube->tex_east,  cube->data->textures[3], collector);

	printf("Textures carregades OK\n");
	// // Test visual: dibuixar textures a la finestra
    // texture_draw_test(game, &cube->tex_north, 10, 10);
	// sleep(2);
    // texture_draw_test(game, &cube->tex_south, 200, 10);
	// sleep(2);
    // texture_draw_test(game, &cube->tex_west,  10, 200);
	// sleep(2);
    // texture_draw_test(game, &cube->tex_east,  200, 200);
	// sleep(2);
    // mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	return (0);
}


//////////////////////////////////////
//// versió de load textures amb MLX42
// mlx_image_t	*load_image(mlx_t *mlx, const char *path)
// {
// 	const char		*ext;
// 	mlx_texture_t	*tex;
// 	mlx_image_t		*img;

// 	if (!mlx || !path)
// 		return (NULL);
// 	// Verificar que el archivo existe
// 	if (access(path, F_OK) != 0)
// 	{
// 		printf("Error: no existe el archivo '%s'\n", path);
// 		return (NULL);
// 	}
// 	printf("load_image - path: %s\n", path);
// 	ext = strrchr(path, '.');
// 	if (!ext)
// 		return (NULL);
// 	// --- PNG ---
// 	if (strcmp(ext, ".png") == 0)
// 	{
// 		tex = mlx_load_png(path);
// 		if (!tex)
// 			return (NULL);
// 		img = mlx_texture_to_image(mlx, tex);
// 		mlx_delete_texture(tex);
// 		return (img);
// 	}
// 	// --- XPM / XPM42 ---
// 	else if (strcmp(ext, ".xpm") == 0 || strcmp(ext, ".xpm42") == 0)
// 	{
// 		printf("load_image es xpm\n");
// 		xpm_t *xpm = mlx_load_xpm42(path);
// 		if (!xpm)
// 			return (NULL);
// 		printf("load_image 2\n");
// 		img = mlx_texture_to_image(mlx, &xpm->texture);
// 		printf("load_image 3\n");
// 		mlx_delete_xpm42(xpm);
// 		printf("load_image 4\n");
// 		return (img);
// 	}
// 	return (NULL);
// }

// int textures_load(t_game *game, t_collector **collector)
// {
//     t_cube *cube = game->cube;

//     cube->tex_north = load_image(game->mlx, cube->data->textures[0]);
//     if (!cube->tex_north)
//         exit_program(collector, "Error: textura NULL NO", EXIT_FAILURE);
//     cube->tex_south = load_image(game->mlx, cube->data->textures[1]);
//     if (!cube->tex_south)
//         exit_program(collector, "Error: textura NULL SO", EXIT_FAILURE);
//     cube->tex_west = load_image(game->mlx, cube->data->textures[2]);
//     if (!cube->tex_west)
//         exit_program(collector, "Error: textura NULL WE", EXIT_FAILURE);
//     cube->tex_east = load_image(game->mlx, cube->data->textures[3]);
//     if (!cube->tex_east)
//         exit_program(collector, "Error: textura NULL EA", EXIT_FAILURE);
//     printf("textures carregades OK\n");
//     return (0);
// }
