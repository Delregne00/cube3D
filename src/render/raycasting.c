/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delregne <delregne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/09 06:02:43 by delregne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	single_ray_cast(t_game *game, t_ray *ray, int x)
{
	ray_init(game, ray, x);
	calc_step_and_side_dist(game, ray);
	dda_perform(game, ray);
	wall_height_calc(game, ray);
	column_textured_draw(game, ray, x);
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
	x = 0;
	while (x < game->width)
	{
		single_ray_cast(game, &ray, x);
		x++;
	}
}
