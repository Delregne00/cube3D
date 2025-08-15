/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/15 12:00:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	cameraX;
	
	cameraX = 2 * x / (double)game->width - 1;
	ray->rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
	ray->rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
	ray->mapX = (int)game->player.x;
	ray->mapY = (int)game->player.y;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

static void	calc_step_and_side_dist(t_game *game, t_ray *ray)
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

static void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->cube->map->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - game->player.x + 
			(1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - game->player.y +
			(1 - ray->stepY) / 2) / ray->rayDirY;
	ray->lineHeight = (int)(game->height / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + game->height / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + game->height / 2;
	if (ray->drawEnd >= game->height)
		ray->drawEnd = game->height - 1;
}

static void	draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		if (y >= 0 && y < game->height)
			mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

static uint32_t	get_wall_color(t_ray *ray)
{
	// NO
	if (ray->side == 0 && ray->rayDirX < 0)
		return (0xFF0000FF);
	// SO
	else if (ray->side == 0 && ray->rayDirX > 0)
		return (0xFFFF00FF);
	// WE
	else if (ray->side == 1 && ray->rayDirY < 0)
		return (0x0000FFFF);
	// EA
	else
		return (0x00FF00FF);
}

static uint32_t	rgb_to_uint32(int r, int g, int b)
{
	// MLX42 usa RGBA en little-endian → 0xRRGGBBAA
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

void	raycasting(t_game *game)
{
	int			x;
	int			y;
	t_ray		ray;
	uint32_t	color_floor;
	uint32_t	color_ceil;

	// Convertimos F y C de game->cube->data a uint32_t
	color_floor = rgb_to_uint32(
		game->cube->data->f_color[0],
		game->cube->data->f_color[1],
		game->cube->data->f_color[2]
	);
	color_ceil = rgb_to_uint32(
		game->cube->data->c_color[0],
		game->cube->data->c_color[1],
		game->cube->data->c_color[2]
	);

	x = 0;
	while (x < game->width)
	{
		init_ray(game, &ray, x);
		calc_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_height(game, &ray);

		// Techo
		y = 0;
		while (y < ray.drawStart)
			mlx_put_pixel(game->img, x, y++, color_ceil);

		// Pared
		draw_vertical_line(game, x, ray.drawStart, ray.drawEnd, get_wall_color(&ray));

		// Suelo
		y = ray.drawEnd + 1;
		while (y < game->height)
			mlx_put_pixel(game->img, x, y++, color_floor);

		x++;
	}
}
