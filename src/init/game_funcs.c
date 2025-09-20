/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/00 11:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	player_init(t_game *game)
{
	t_map	*map;
	int		player_x;
	int		player_y;
	char	player_dir;

	map = game->cube->map;
	player_x = map->player_x;
	player_y = map->player_y;
	player_dir = map->player_dir;
	game->player.x = (double)player_x + 0.5;
	game->player.y = (double)player_y + 0.5;
	player_set_direction(&game->player, player_dir);
	map->map[player_y][player_x] = '0';
}

int	window_close(t_game_loop_param *p)
{
	collector_cleanup(p->collector, p->game->mlx);
	exit(0);
	return (0);
}

int	game_loop(void *param)
{
	t_game_loop_param	*p;
	t_game				*game;

	p = (t_game_loop_param *)param;
	game = p->game;
	ft_memset(game->addr, 0, WIN_W * WIN_H * (game->bits_per_pixel / 8));
	handle_input(p);
	raycasting(game);
	minimap_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	hooks_setup(t_game_loop_param *p)
{
	mlx_hook(p->game->win, 2, 1L << 0, key_press, p->game);
	mlx_hook(p->game->win, 3, 1L << 1, key_release, p->game);
	mlx_hook(p->game->win, 17, 1L << 17, window_close, p);
	mlx_loop_hook(p->game->mlx, game_loop, p);
}
