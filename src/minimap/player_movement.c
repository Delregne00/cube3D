/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/20 20:29:06 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static bool	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	row_len;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->cube->map->filas)
		return (true);
	row_len = ft_strlen(game->cube->map->map[map_y]);
	if (map_x >= row_len)
		return (true);
	return (game->cube->map->map[map_y][map_x] == '1');
}

// Moviment endavant/enrera
void	player_move(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.x + game->player.dir_x * move_speed * direction;
	new_y = game->player.y + game->player.dir_y * move_speed * direction;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

// Movimient lateral
void	player_strafe(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.x + game->player.plane_x * move_speed * direction;
	new_y = game->player.y + game->player.plane_y * move_speed * direction;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

// Rotació del jugador
void	player_rotate(t_game *game, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed * direction)
		- game->player.dir_y * sin(rot_speed * direction);
	game->player.dir_y = old_dir_x * sin(rot_speed * direction)
		+ game->player.dir_y * cos(rot_speed * direction);
	game->player.plane_x = game->player.plane_x * cos(rot_speed * direction)
		- game->player.plane_y * sin(rot_speed * direction);
	game->player.plane_y = old_plane_x * sin(rot_speed * direction)
		+ game->player.plane_y * cos(rot_speed * direction);
}
