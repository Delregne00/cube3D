/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_keys.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/21 15:55:01 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

// Manejo de teclas presionadas
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->cube->keys->w = 1;
	else if (keycode == KEY_A)
		game->cube->keys->a = 1;
	else if (keycode == KEY_S)
		game->cube->keys->s = 1;
	else if (keycode == KEY_D)
		game->cube->keys->d = 1;
	else if (keycode == KEY_LEFT)
		game->cube->keys->left = 1;
	else if (keycode == KEY_RIGHT)
		game->cube->keys->right = 1;
	else if (keycode == KEY_ESC)
		game->cube->keys->esc = 1;
	return (0);
}

// Manejo de teclas liberadas
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->cube->keys->w = 0;
	else if (keycode == KEY_A)
		game->cube->keys->a = 0;
	else if (keycode == KEY_S)
		game->cube->keys->s = 0;
	else if (keycode == KEY_D)
		game->cube->keys->d = 0;
	else if (keycode == KEY_LEFT)
		game->cube->keys->left = 0;
	else if (keycode == KEY_RIGHT)
		game->cube->keys->right = 0;
	else if (keycode == KEY_ESC)
		game->cube->keys->esc = 0;
	return (0);
}

// Procesa la entrada del usuario
void	handle_input(t_game_loop_param *p)
{
	if (p->game->cube->keys->w)
		player_move(p->game, 1);
	if (p->game->cube->keys->s)
		player_move(p->game, -1);
	if (p->game->cube->keys->a)
		player_strafe(p->game, -1);
	if (p->game->cube->keys->d)
		player_strafe(p->game, 1);
	if (p->game->cube->keys->left)
		player_rotate(p->game, -1);
	if (p->game->cube->keys->right)
		player_rotate(p->game, 1);
	if (p->game->cube->keys->esc)
		window_close(p);
}
