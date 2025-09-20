/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/20 20:25:28 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static bool	check_wall_hit(t_game *game, t_ray *ray)
{
	char	**map;
	int		row_len;

	map = game->cube->map->map;
	if (ray->map_y < 0 || ray->map_y >= game->cube->map->filas)
		return (true);
	if (ray->map_x < 0)
		return (true);
	row_len = ft_strlen(map[ray->map_y]);
	if (ray->map_x >= row_len)
		return (true);
	return (map[ray->map_y][ray->map_x] == '1');
}

static bool	check_bounds(t_game *game, t_ray *ray)
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

static void	dda_step(t_ray *ray)
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

void	dda_perform(t_game *game, t_ray *ray)
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
