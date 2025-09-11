/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/11 12:22:41 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	init_mlx_and_window(t_game *game, t_collector **collector)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_program(collector, "Error Failed to initialize MLX",
			EXIT_FAILURE, NULL);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		exit_program(collector, "Error Failed to create window",
			EXIT_FAILURE, game->mlx);
	collector_append(collector, game->win, RES_WIN, game->mlx);
}

static void	init_image_and_buffer(t_game *game, t_collector **collector)
{
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		exit_program(collector, "Error Failed to create image",
			EXIT_FAILURE, game->mlx);
	collector_append(collector, game->img, RES_IMG, game->mlx);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		exit_program(collector, "Error Failed to create addr",
			EXIT_FAILURE, game->mlx);
}

static t_game_loop_param	*create_loop_param(t_game *game,
	t_collector **collector)
{
	t_game_loop_param	*loop_param;

	loop_param = malloc(sizeof(t_game_loop_param));
	if (!loop_param)
		exit_program(collector, "Error: Failed to initialize loop_param",
			EXIT_FAILURE, game->mlx);
	collector_append(collector, loop_param, RES_MALLOC, game->mlx);
	loop_param->game = game;
	loop_param->collector = collector;
	return (loop_param);
}

static t_game	*init_basic_game(t_cube *cube, t_collector **collector)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_program(collector, "Error malloc game", EXIT_FAILURE, NULL);
	collector_append(collector, game, RES_MALLOC, NULL);
	game->cube = cube;
	game->width = WIN_W;
	game->height = WIN_H;
	game->cache.initialized = 0;
	game->cache.floor_color = 0;
	game->cache.ceil_color = 0;
	game->cache.sin_rot = 0.0;
	game->cache.cos_rot = 0.0;
	ft_memset(game->cache.tex_cache, 0, sizeof(game->cache.tex_cache));
	return (game);
}

t_game	*game_init(t_cube *cube, t_collector **collector)
{
	t_game				*game;
	t_game_loop_param	*loop_param;

	game = init_basic_game(cube, collector);
	init_mlx_and_window(game, collector);
	init_image_and_buffer(game, collector);
	textures_load(game, collector);
	player_init(game);
	loop_param = create_loop_param(game, collector);
	hooks_setup(loop_param);
	mlx_loop(game->mlx);
	return (game);
}
