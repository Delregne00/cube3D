/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/09/02 18:04:28 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

t_render_cache g_cache;

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)game->width - 1;
	ray->rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
	ray->rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
	ray->mapX = (int)game->player.x;
	ray->mapY = (int)game->player.y;
	init_ray_distances(ray);
}

void	init_ray_distances(t_ray *ray)
{
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1.0 / ray->rayDirX);

	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1.0 / ray->rayDirY);
}

void	calc_step_and_side_dist(t_game *game, t_ray *ray)
{
	calc_step_x(game, ray);
	calc_step_y(game, ray);
}

void	calc_step_x(t_game *game, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->player.x) * ray->deltaDistX;
	}
}

void	calc_step_y(t_game *game, t_ray *ray)
{
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player.y) * ray->deltaDistY;
	}
}

