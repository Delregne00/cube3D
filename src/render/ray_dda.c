/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:03:00 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		dda_step(ray);
		if (check_bounds(game, ray))
			break ;
		if (check_wall_hit(game, ray))
			ray->hit = 1;
	}
}

void	dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

bool	check_bounds(t_game *game, t_ray *ray)
{
	int	max_cols;
	int	max_rows;

	max_cols = game->cube->map->max_columnas;
	max_rows = game->cube->map->filas;
	if (ray->map_x < 0 || ray->map_y < 0)
	{
		ray->hit = 1;
		return (true);
	}
	if (ray->map_y >= max_rows || ray->map_x >= max_cols)
	{
		ray->hit = 1;
		return (true);
	}
	return (false);
}

bool	check_wall_hit(t_game *game, t_ray *ray)
{
	char	**map;

	map = game->cube->map->map;
	return (map[ray->map_y][ray->map_x] == '1');
}
