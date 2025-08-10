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
void game_loop(void *param)
{
    t_game *game = (t_game *)param;
    
    // Limpiar la imagen (fondo negro)
    ft_memset(game->img->pixels, 0, WIN_W * WIN_H * sizeof(uint32_t));
    
    // Manejar input
    handle_input(game);
    
    // Renderizar minimap
    render_minimap(game);
}

// game_init() modificado
t_game *game_init(t_cube *cube, t_collector **collector)
{
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
    {
        printf("Error: Failed to allocate memory for game\n");
        return (NULL);
    }
    
    if (collector)
    {
        collector_append(collector, game);
        game->collector = *collector;
    }
    
    game->cube = cube;
    game->width = WIN_W;
    game->height = WIN_H;
    
    // Inicializar MLX
    game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
    if (!game->mlx)
    {
        perror("Failed to initialize MLX");
        free(game);
        exit(1);
    }
    
    // Crear imagen
    game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!game->img)
    {
        perror("Failed to create image");
        mlx_terminate(game->mlx);
        free(game);
        exit(1);
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
    // Ajustado para el sistema de coordenadas correcto
    switch (game->cube->map->player_dir)
    {
        case 'N':
            game->player.dir_x = -1.0;
            game->player.dir_y = 0.0;
            game->player.plane_x = 0.0;
            game->player.plane_y = 0.66;
            break;
        case 'S':
            game->player.dir_x = 1.0;
            game->player.dir_y = 0.0;
            game->player.plane_x = 0.0;
            game->player.plane_y = -0.66;
            break;
        case 'E':
            game->player.dir_x = 0.0;
            game->player.dir_y = 1.0;
            game->player.plane_x = 0.66;
            game->player.plane_y = 0.0;
            break;
        case 'W':
            game->player.dir_x = 0.0;
            game->player.dir_y = -1.0;
            game->player.plane_x = -0.66;
            game->player.plane_y = 0.0;
            break;
    }
}

// static void	set_direction(t_player *p, char dir)
// {
// 	if (dir == 'N')
// 	{
// 		p->dir_x = 0;
// 		p->dir_y = -1;
// 		p->plane_x = 0.66;
// 		p->plane_y = 0;
// 	}
// 	else if (dir == 'S')
// 	{
// 		p->dir_x = 0;
// 		p->dir_y = 1;
// 		p->plane_x = -0.66;
// 		p->plane_y = 0;
// 	}
// 	else if (dir == 'E')
// 	{
// 		p->dir_x = 1;
// 		p->dir_y = 0;
// 		p->plane_x = 0;
// 		p->plane_y = 0.66;
// 	}
// 	else if (dir == 'W')
// 	{
// 		p->dir_x = -1;
// 		p->dir_y = 0;
// 		p->plane_x = 0;
// 		p->plane_y = -0.66;
// 	}
// }

// static void	player_init(t_game *game)
// {
// 	game->player.x = 4.5;
// 	game->player.y = 3.5;
// 	set_direction(&game->player, game->cube->map->player_dir);
// }

// t_game	*game_init(t_cube *cube, t_collector **collector)
// {
// 	t_game	*game;
// 	// int x, y;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 	{
// 		printf("KKlavaK\n");
// 		return (NULL);
// 	}
// 	if (collector)
// 	{
// 		collector_append(collector, game);
// 		game->collector = *collector;
// 	}
// 	game->cube = cube;
// 	// game->player	= player;
// 	game->mlx = 0;
// 	game->win = 0;
// 	game->img = 0;
// 	game->addr = 0;
// 	game->width = 0;
// 	game->height = 0;
// 	if (load_textures(game->cube))
// 	{
// 		free(game);
// 		exit(1);
// 	}
// 	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
// 	if (!game->mlx)
// 	{
// 		perror("Failed to initialize MLX");
// 		free(game);
// 		exit(1);
// 	}
// 	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
// 	if (!game->img)
// 	{
// 		perror("Failed to create image");
// 		mlx_terminate(game->mlx);
// 		free(game);
// 		exit(1);
// 	}
// //	game->addr = mlx_get_image_buffer(game->img);
// 	printf("game_init 1\n");
// 	player_init(game);
// 	printf("game_init 2\n");
// 	render_raycast(game);
// 	printf("game_init 3\n");
// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// 	printf("game_init 4\n");
// 	mlx_loop(game->mlx);
// 	printf("game_init 5\n");
// 	mlx_terminate(game->mlx);
// 	printf("game_init 6\n");
// 	return (game);
// }