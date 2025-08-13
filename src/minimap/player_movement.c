/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

// Función principal de input del jugador
void handle_input(t_game *game)
{
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        move_player(game, 1);  // Adelante
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        move_player(game, -1); // Atrás
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
        strafe_player(game, -1); // Izquierda
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
        strafe_player(game, 1);  // Derecha
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        rotate_player(game, -1); // Rotar izquierda
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        rotate_player(game, 1);  // Rotar derecha
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);  // Esto hará que mlx_loop() termine
}

// Movimiento adelante/atrás
void move_player(t_game *game, int direction)
{
    double new_x, new_y;
    double move_speed = 0.05; // Ajusta según necesites
    
    // Moverse en la dirección hacia donde mira el jugador
    new_x = game->player.x + game->player.dir_x * move_speed * direction;
    new_y = game->player.y + game->player.dir_y * move_speed * direction;
    
    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

// Movimiento lateral
void strafe_player(t_game *game, int direction)
{
    double new_x, new_y;
    double move_speed = 0.05;
    
    // Perpendicular al vector de dirección (usar plane)
    new_x = game->player.x + game->player.plane_x * move_speed * direction;
    new_y = game->player.y + game->player.plane_y * move_speed * direction;
    
    if (!is_wall(game, new_x, game->player.y))
        game->player.x = new_x;
    if (!is_wall(game, game->player.x, new_y))
        game->player.y = new_y;
}

// Rotación del jugador
void rotate_player(t_game *game, int direction)
{
    double rot_speed = 0.03; // Ajusta según necesites
    double old_dir_x, old_plane_x;
    
    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    
    game->player.dir_x = game->player.dir_x * cos(rot_speed * direction) - 
                        game->player.dir_y * sin(rot_speed * direction);
    game->player.dir_y = old_dir_x * sin(rot_speed * direction) + 
                        game->player.dir_y * cos(rot_speed * direction);
    game->player.plane_x = game->player.plane_x * cos(rot_speed * direction) - 
                          game->player.plane_y * sin(rot_speed * direction);
    game->player.plane_y = old_plane_x * sin(rot_speed * direction) + 
                          game->player.plane_y * cos(rot_speed * direction);
}

// Verificar si hay una pared
bool is_wall(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_y < 0 || 
        map_y >= game->cube->map->filas || 
        map_x >= game->cube->map->max_columnas)
        return (true);
    
    return (game->cube->map->map[map_y][map_x] == '1');
}