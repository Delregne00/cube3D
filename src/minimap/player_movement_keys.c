/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_keys.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/05 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

// Variable global x estat de tecles
t_keys	g_keys = {0, 0, 0, 0, 0, 0, 0};

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
		window_close(p);
}
