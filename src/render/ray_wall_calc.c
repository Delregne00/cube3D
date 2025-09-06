/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:05:01 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	calc_wall_height(t_game *game, t_ray *ray)
{
	calc_perp_wall_dist(game, ray);
	calc_line_height(game, ray);
	calc_draw_limits(game, ray);
}

void	calc_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perpWallDist = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2) / ray->rayDirX;
	}
	else
	{
		ray->perpWallDist = (ray->map_y - game->player.y
				+ (1 - ray->stepY) / 2) / ray->rayDirY;
	}
}

void	calc_line_height(t_game *game, t_ray *ray)
{
	ray->lineHeight = (int)(game->height / ray->perpWallDist);
}

void	calc_draw_limits(t_game *game, t_ray *ray)
{
	ray->drawStart = -ray->lineHeight / 2 + game->height / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + game->height / 2;
	if (ray->drawEnd >= game->height)
		ray->drawEnd = game->height - 1;
}
