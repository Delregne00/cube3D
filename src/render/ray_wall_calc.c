/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ray_wall_calc.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:57:18 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:57:18 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "includes/cube.h"

static void	calc_draw_limits(t_game *game, t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + game->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->height / 2;
	if (ray->draw_end >= game->height)
		ray->draw_end = game->height - 1;
}

static void	calc_line_height(t_game *game, t_ray *ray)
{
	ray->line_height = (int)(game->height / ray->perp_wall_dist);
}

static void	calc_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - game->player.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
}

void	wall_height_calc(t_game *game, t_ray *ray)
{
	calc_perp_wall_dist(game, ray);
	calc_line_height(game, ray);
	calc_draw_limits(game, ray);
}
