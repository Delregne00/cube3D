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

// Variable global x estat de tecles
t_keys g_keys = {0, 0, 0, 0, 0, 0, 0};

// Maneig tecles pressionades
int	key_press(int keycode, t_game *game)
{
	(void)game;
	if (keycode == KEY_W)
		g_keys.w = 1;
	else if (keycode == KEY_A)
		g_keys.a = 1;
	else if (keycode == KEY_S)
		g_keys.s = 1;
	else if (keycode == KEY_D)
		g_keys.d = 1;
	else if (keycode == KEY_LEFT)
		g_keys.left = 1;
	else if (keycode == KEY_RIGHT)
		g_keys.right = 1;
	else if (keycode == KEY_ESC)
		g_keys.esc = 1;
	return (0);
}

// Maneig tecles lliberades
int	key_release(int keycode, t_game *game)
{
	(void)game;
	if (keycode == KEY_W)
		g_keys.w = 0;
	else if (keycode == KEY_A)
		g_keys.a = 0;
	else if (keycode == KEY_S)
		g_keys.s = 0;
	else if (keycode == KEY_D)
		g_keys.d = 0;
	else if (keycode == KEY_LEFT)
		g_keys.left = 0;
	else if (keycode == KEY_RIGHT)
		g_keys.right = 0;
	else if (keycode == KEY_ESC)
		g_keys.esc = 0;
	return (0);
}

// // Input del jugador MLX42
// void	handle_input(t_game *game)
// {
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
// 		move_player(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
// 		move_player(game, -1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
// 		strafe_player(game, -1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
// 		strafe_player(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		rotate_player(game, -1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		rotate_player(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(game->mlx);
// }

// Input del jugador minilibX
// void	handle_input(t_game *game)
void	handle_input(t_game_loop_param *p)
{
	if (g_keys.w)
		move_player(p->game, 1);
	if (g_keys.s)
		move_player(p->game, -1);
	if (g_keys.a)
		strafe_player(p->game, -1);
	if (g_keys.d)
		strafe_player(p->game, 1);
	if (g_keys.left)
		rotate_player(p->game, -1);
	if (g_keys.right)
		rotate_player(p->game, 1);
	if (g_keys.esc)
		close_window(p);
}

bool	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || 
		map_y >= game->cube->map->filas || 
		map_x >= game->cube->map->max_columnas)
		return (true);
	return (game->cube->map->map[map_y][map_x] == '1');
}

// Moviment endavant/enrera
void	move_player(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_speed;
	
	move_speed = 0.05; // TODO: Ajustar?
	// Moure's en la direcció cap on mira el jugador
	new_x = game->player.x + game->player.dir_x * move_speed * direction;
	new_y = game->player.y + game->player.dir_y * move_speed * direction;
	
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

// Movimient lateral
void strafe_player(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_speed;
	
	move_speed = 0.05;
	// Perpendicular al vector de direcció
	new_x = game->player.x + game->player.plane_x * move_speed * direction;
	new_y = game->player.y + game->player.plane_y * move_speed * direction;
	
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

// Rotació del jugador
void rotate_player(t_game *game, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.03; // TODO: Ajustar?
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
