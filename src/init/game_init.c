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

static void	player_init(t_game *game)
{
	game->player.x = 4.5;
	game->player.y = 3.5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

t_game	*game_init(t_cube *cube, t_collector **collector)
{
	t_game	*game;
	// int x, y;

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
	// game->tex_north = load_texture(cube->tex_north);
	// game->tex_south = load_texture(cube->tex_south);
	// game->tex_west  = load_texture(cube->tex_west);
	// game->tex_east  = load_texture(cube->tex_east);
	if (load_textures(game->cube))
	{
		free(game);
		exit(1);
	}
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
	printf("game_init 1\n");
	player_init(game);
	printf("game_init 2\n");
	render_raycast(game);
	printf("game_init 3\n");
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	printf("game_init 4\n");
	mlx_loop(game->mlx);
	printf("game_init 5\n");
	mlx_terminate(game->mlx);
	printf("game_init 6\n");
	return (game);
}