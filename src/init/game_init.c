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

// Función de loop principal para el minimap
void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// Limpiar la imagen (fondo negro)
	ft_memset(game->img->pixels, 0, WIN_W * WIN_H * sizeof(uint32_t));
	// Manejar input
	handle_input(game);
	// Raycasting básico (pintado de muros)
	raycasting(game);
	// Renderizar minimap encima
	render_minimap(game);
}

t_game *game_init(t_cube *cube, t_collector **collector)
{
		t_game *game;

		game = malloc(sizeof(t_game));
		if (!game)
		return (NULL);
		collector_append(collector, game);
		game->cube = cube;
		game->width = WIN_W;
		game->height = WIN_H;
		// Inicializar MLX
		game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
		if (!game->mlx)
		exit_program(collector, "Error Failed to initialize MLX", EXIT_FAILURE);
		// Crear imagen
		game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
		if (!game->img)
		{
		mlx_terminate(game->mlx);
		exit_program(collector, "Error Failed to create image", EXIT_FAILURE);
	}
		// Inicializar jugador
		player_init(game);
		// Añadir imagen a la ventana
		mlx_image_to_window(game->mlx, game->img, 0, 0);
		// Configurar el loop hook para el minimap
		mlx_loop_hook(game->mlx, game_loop, game);
		// Iniciar el loop
		mlx_loop(game->mlx);
		// Limpiar
		mlx_terminate(game->mlx);
		return (game);
}

// Función player_init() que necesitas crear/modificar
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
		// Substituir player’s start position (NSWE) per 0 (empty space)
		game->cube->map->map[game->cube->map->player_y][game->cube->map->player_x] = '0';
		print_map(game->cube->map);
}
