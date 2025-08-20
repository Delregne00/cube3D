/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delregne <delregne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/20 12:46:19 by delregne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void player_init(t_game *game)
{
		// Usar la posición del parsing
		game->player.x = (double)game->cube->map->player_x + 0.5;
		game->player.y = (double)game->cube->map->player_y + 0.5;
		// Configurar dirección inicial según el carácter del mapa
		switch (game->cube->map->player_dir)
		{
		case 'N': // Norte = hacia arriba en el minimap
			game->player.dir_x = 0.0;
			game->player.dir_y = -1.0;
			game->player.plane_x = 0.66;
			game->player.plane_y = 0.0;
			break;
		case 'S': // Sur = hacia abajo en el minimap
			game->player.dir_x = 0.0;
			game->player.dir_y = 1.0;
			game->player.plane_x = -0.66;
			game->player.plane_y = 0.0;
			break;
		case 'E': // Este = hacia la derecha en el minimap
			game->player.dir_x = 1.0;
			game->player.dir_y = 0.0;
			game->player.plane_x = 0.0;
			game->player.plane_y = 0.66;
			break;
		case 'W': // Oeste = hacia la izquierda en el minimap
			game->player.dir_x = -1.0;
			game->player.dir_y = 0.0;
			game->player.plane_x = 0.0;
			game->player.plane_y = -0.66;
			break;
		}
		// Substituir player’s start position (NSEW) per 0 (empty space)
		game->cube->map->map[game->cube->map->player_y][game->cube->map->player_x] = '0';
		// print_map(game->cube->map);
}

// int	close_window(t_game *game)
int	close_window(t_game_loop_param *p)
{
	// printf("marxaaaaa!\n");
	// (void)game;
	collector_cleanup(p->collector, p->game->mlx);
	printf("Surt de cub3D sense errors x close_window!\n");
	exit(0);
	return (0);
}

// void	game_loop(void *param)
int	game_loop(void *param)
{
	t_game_loop_param	*p;
	t_game				*game;

	p = (t_game_loop_param *)param;
	game = p->game;
	ft_memset(game->addr, 0, WIN_W * WIN_H * (game->bits_per_pixel / 8));
	// handle_input(game);
	handle_input(p);
	raycasting(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

// Configurar hooks de minilibX
void	hooks_setup(t_game_loop_param *p)
{
	mlx_hook(p->game->win, 2, 1L<<0, key_press, p->game);      // KeyPress
	mlx_hook(p->game->win, 3, 1L<<1, key_release, p->game);    // KeyRelease  
	// mlx_hook(p->game->win, 17, 1L<<17, close_window, p->game); // DestroyNotify (X)
	mlx_hook(p->game->win, 17, 1L<<17, close_window, p); // DestroyNotify (X)
	mlx_loop_hook(p->game->mlx, game_loop, p);          // Loop hook
}

// void	game_loop(void *param)
// {
//     t_game_loop_param	*p;
//     t_game				*game;
//     t_collector			**collector;

//     p = (t_game_loop_param *)param;
//     game = p->game;
//     collector = p->collector;
// 	// Limpiar la imagen (fondo negro)
// 	ft_memset(game->img->pixels, 0, WIN_W * WIN_H * sizeof(uint32_t));
// 	// Manejar input
// 	handle_input(game);
// 	// Raycasting básico (pintado de muros)
// 	raycasting(game, collector);
// 	// Renderizar minimap encima
// 	render_minimap(game);
// }

t_game *game_init(t_cube *cube, t_collector **collector)
{
	t_game				*game;
	t_game_loop_param	*loop_param;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_program(collector, "Error malloc game", EXIT_FAILURE, NULL);
	collector_append(collector, game, RES_MALLOC, NULL);

	game->cube = cube;
	game->width = WIN_W;
	game->height = WIN_H;

	// Inicializar MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_program(collector, "Error Failed to initialize MLX", EXIT_FAILURE, NULL);

	// Crear ventana
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		exit_program(collector, "Error Failed to create window", EXIT_FAILURE, game->mlx);
	collector_append(collector, game->win, RES_WIN, game->mlx);

	// Crear imagen
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		exit_program(collector, "Error Failed to create image", EXIT_FAILURE, game->mlx);
	collector_append(collector, game->img, RES_IMG, game->mlx);

	game->addr = mlx_get_data_addr(game->img,
									&game->bits_per_pixel,
									&game->line_length,
									&game->endian);
	if (!game->addr)
		exit_program(collector, "Error Failed to create addr", EXIT_FAILURE, game->mlx);

	// Cargar texturas
	textures_load(game, collector);


	// Inicializar jugador
	player_init(game);

	// Configurar loop hook
	loop_param = malloc(sizeof(t_game_loop_param));
	if (!loop_param)
		exit_program(collector, "Error: Failed to initialize loop_param", EXIT_FAILURE, game->mlx);
	collector_append(collector, loop_param, RES_MALLOC, game->mlx);
	loop_param->game = game;
	loop_param->collector = collector;

	// MiniLibX oficial no té mlx_loop_hook amb parametre directe, hem de fer-ho amb un hook
	// mlx_loop_hook(game->mlx, game_loop, loop_param);
	hooks_setup(loop_param);

	// Iniciar loop
	mlx_loop(game->mlx);
	return (game);
}
