/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/07/26 09:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

// static void	game_init_mlx(t_game *game)
// {
// 	game->mlx = 0;
// 	game->win = 0;
// 	game->img = 0;
// 	game->addr = 0;
// }

t_game	*game_init(t_cube *cube, t_collector **collector)
{
	t_game	*game;
	int x, y;

    game = malloc(sizeof(t_game));
    if (!game)
	{
		printf("KKlavaK\n");
        return (NULL);
	}
	if (collector)
	{
		collector_append(collector, game);
		game->collector = *collector;
	}
	game->cube = cube;
    // game->player	= player;
	game->mlx = 0;
	game->win = 0;
	game->img = 0;
	game->addr = 0;
    game->width = 0;
    game->height = 0;

	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!game->mlx)
	{
		perror("Failed to initialize MLX");
		free(game);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
	{
		perror("Failed to create image");
		mlx_terminate(game->mlx);
		free(game);
		exit(1);
	}
//	game->addr = mlx_get_image_buffer(game->img);

    // Mostrem la imatge primer
    if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
    {
        fprintf(stderr, "mlx_image_to_window failed\n");
        mlx_terminate(game->mlx);
		free(game);
		exit(1);
    }

    // Ara pintem a la imatge (que ja és visible)
    for (y = 100; y < 250; y++)
    {
        for (x = 100; x < 300; x++)
        {
            mlx_put_pixel(game->img, x, y, 0xFF0000FF); // RGBA: vermell opac
        }
    }

    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);

	return (game);
}