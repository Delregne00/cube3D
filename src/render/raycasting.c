/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:06:34 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	single_ray_cast(t_game *game, t_ray *ray, int x)
{
	ray_init(game, ray, x);
	calc_step_and_side_dist(game, ray);
	dda_perform(game, ray);
	calc_wall_height(game, ray);
	draw_column_textured(game, ray, x);
}

static void	display_fps(void)
{
	static int		frame_count;
	static time_t	last_time;
	time_t			current_time;

	frame_count = 0;
	last_time = 0;
	current_time = time(NULL);
	frame_count++;
	if (current_time > last_time)
	{
		printf("FPS: %d\n", frame_count);
		frame_count = 0;
		last_time = current_time;
	}
}

static void	cache_init(t_game *game)
{
	if (!g_cache.initialized)
		cache_init_render(game);
}

static bool	game_data_validate(t_game *game)
{
	if (!game || !game->cube || !game->cube->map)
		return (false);
	return (true);
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	if (!game_data_validate(game))
		return ;
	cache_init(game);
	display_fps();
	x = 0;
	while (x < game->width)
	{
		single_ray_cast(game, &ray, x);
		x++;
	}
}
