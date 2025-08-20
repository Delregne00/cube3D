/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delregne <delregne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/20 18:20:44 by delregne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"
#include <stdint.h>

// Colores básicos para las paredes
#define COLOR_WALL_NORTH  0xFF0000  // Rojo
#define COLOR_WALL_SOUTH  0x00FF00  // Verde  
#define COLOR_WALL_EAST   0x0000FF  // Azul
#define COLOR_WALL_WEST   0xFFFF00  // Amarillo

// Declaraciones de funciones
static uint32_t	rgb_to_color(int r, int g, int b);
static uint32_t	select_wall_color(t_ray *ray);
static void	put_pixel_safe(t_game *game, int x, int y, uint32_t color);
static void	draw_column_basic(t_game *game, t_ray *ray, int x, 
						uint32_t floor_color, uint32_t ceil_color);

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
		
		// Verificar límites del mapa
		if (ray->mapX < 0 || ray->mapY < 0 || 
			ray->mapY >= game->cube->map->filas || 
			ray->mapX >= game->cube->map->max_columnas)
		{
			ray->hit = 1; // Tratar bordes como paredes
			break;
		}
		
		// Verificar si hay una pared
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

// Convertir RGB a formato de color para minilibX
static uint32_t	rgb_to_color(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

// Seleccionar color según la orientación de la pared
static uint32_t	select_wall_color(t_ray *ray)
{
	if (ray->side == 0) // Paredes verticales (NS)
	{
		if (ray->rayDirX > 0)
			return COLOR_WALL_EAST;   // Mirando hacia el este
		else
			return COLOR_WALL_WEST;   // Mirando hacia el oeste
	}
	else // Paredes horizontales (EW)
	{
		if (ray->rayDirY > 0)
			return COLOR_WALL_SOUTH;  // Mirando hacia el sur
		else
			return COLOR_WALL_NORTH;  // Mirando hacia el norte
	}
}

// Poner pixel de forma segura
static void	put_pixel_safe(t_game *game, int x, int y, uint32_t color)
{
	char	*pixel;

	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return;
	
	pixel = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(uint32_t *)pixel = color;
}

// Dibujar una columna completa (techo + pared + suelo)
static void	draw_column_basic(t_game *game, t_ray *ray, int x, 
							uint32_t floor_color, uint32_t ceil_color)
{
	int			y;
	uint32_t	wall_color;

	wall_color = select_wall_color(ray);
	
	// 1️⃣ Dibujar techo
	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel_safe(game, x, y, ceil_color);
		y++;
	}
	
	// 2️⃣ Dibujar pared
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		put_pixel_safe(game, x, y, wall_color);
		y++;
	}
	
	// 3️⃣ Dibujar suelo
	y = ray->drawEnd + 1;
	while (y < game->height)
	{
		put_pixel_safe(game, x, y, floor_color);
		y++;
	}
}

// Función principal de raycasting con colores básicos
void	raycasting(t_game *game)
{
	int			x;
	t_ray		ray;
	uint32_t	color_floor;
	uint32_t	color_ceil;

	// Convertir colores del cube a formato minilibX
	color_floor = rgb_to_color(
		game->cube->data->f_color[0],
		game->cube->data->f_color[1],
		game->cube->data->f_color[2]
	);
	color_ceil = rgb_to_color(
		game->cube->data->c_color[0],
		game->cube->data->c_color[1],
		game->cube->data->c_color[2]
	);

	x = 0;
	while (x < game->width)
	{
		// Procesar cada columna de píxeles
		init_ray(game, &ray, x);
		calc_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_height(game, &ray);
		
		// Dibujar la columna
		draw_column_basic(game, &ray, x, color_floor, color_ceil);
		
		x++;
	}
}

/* CÓDIGO COMENTADO - Versión anterior con texturas
// Esta será tu referencia cuando implementes texturas más adelante

static uint32_t get_texture_pixel(mlx_image_t *img, int texX, int texY)
{
    int index = (texY * img->width + texX) * 4;
    return ((img->pixels[index] << 24)     // R
        | (img->pixels[index + 1] << 16)   // G
        | (img->pixels[index + 2] << 8)    // B
        | (img->pixels[index + 3]));       // A
}

static mlx_image_t *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->rayDirX < 0)
            return (game->cube->tex_north);
        else
            return (game->cube->tex_south);
    }
    else
    {
        if (ray->rayDirY < 0)
            return (game->cube->tex_west);
        else
            return (game->cube->tex_east);
    }
}
*/




//// les 3 funcions següents funcionen OK però amb textures en loc de images
// static uint32_t	get_texture_pixel(mlx_texture_t *tex, int texX, int texY)
// {
// 	int	index = (texY * tex->width + texX) * 4;
// 	return ((tex->pixels[index] << 24)     // R
// 		| (tex->pixels[index + 1] << 16)  // G
// 		| (tex->pixels[index + 2] << 8)   // B
// 		| (tex->pixels[index + 3]));      // A
// }

// static mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
// {
// 	if (ray->side == 0)
// 	{
// 		if (ray->rayDirX < 0)
// 			return (game->cube->tex_north);
// 		else
// 			return (game->cube->tex_south);
// 	}
// 	else
// 	{
// 		if (ray->rayDirY < 0)
// 			return (game->cube->tex_west);
// 		else
// 			return (game->cube->tex_east);
// 	}
// }

// void	raycasting(t_game *game)
// {
// 	int			x;
// 	int			y;
// 	t_ray		ray;
// 	uint32_t	color_floor;
// 	uint32_t	color_ceil;

// 	color_floor = rgb_to_uint32(
// 		game->cube->data->f_color[0],
// 		game->cube->data->f_color[1],
// 		game->cube->data->f_color[2]
// 	);
// 	color_ceil = rgb_to_uint32(
// 		game->cube->data->c_color[0],
// 		game->cube->data->c_color[1],
// 		game->cube->data->c_color[2]
// 	);

// 	x = 0;
// 	while (x < game->width)
// 	{
// 		init_ray(game, &ray, x);
// 		calc_step_and_side_dist(game, &ray);
// 		perform_dda(game, &ray);
// 		calc_wall_height(game, &ray);

// 		// 1️⃣ Techo
// 		y = 0;
// 		while (y < ray.drawStart)
// 			mlx_put_pixel(game->img, x, y++, color_ceil);

// 		// 2️⃣ Pared con textura
// 		mlx_texture_t *tex = select_texture(game, &ray);
// 		if (!tex)
// 		{
// 			printf("Error: textura NULL\n");
// 			continue; // o salir
// 		}

// 		double wallX;
// 		if (ray.side == 0)
// 			wallX = game->player.y + ray.perpWallDist * ray.rayDirY;
// 		else
// 			wallX = game->player.x + ray.perpWallDist * ray.rayDirX;
// 		wallX -= floor(wallX);

// 		int texX = (int)(wallX * (double)tex->width);
// 		if ((ray.side == 0 && ray.rayDirX > 0) ||
// 			(ray.side == 1 && ray.rayDirY < 0))
// 			texX = tex->width - texX - 1;

// 		double step = 1.0 * tex->height / ray.lineHeight;
// 		if (ray.drawStart < 0)
// 			ray.drawStart = 0;
// 		if (ray.drawEnd >= game->height)
// 			ray.drawEnd = game->height - 1;

// 		double texPos = (ray.drawStart - game->height / 2.0 + ray.lineHeight / 2.0) * step;

// 		int texY;
// 		texY = 0;
// 		for (y = ray.drawStart; y <= ray.drawEnd; y++)
// 		{
// 			// texY = (int)texPos & (tex->height - 1);
// 			texY = (int)texPos % tex->height;
// 			if (texY < 0)
// 				texY += tex->height;

// 			texPos += step;
// 			uint32_t color = get_texture_pixel(tex, texX, texY);
// 			mlx_put_pixel(game->img, x, y, color);
// 		}
// 		if (texX < 0 || (uint32_t)texX >= tex->width || texY < 0 || (uint32_t)texY >= tex->height)
// 		{
// 			printf("Error: texX=%d texY=%d fuera de rango (w=%d h=%d)\n",
// 				texX, texY, tex->width, tex->height);
// 			continue;
// 		}

// 		// 3️⃣ Suelo
// 		y = ray.drawEnd + 1;
// 		while (y < game->height)
// 			mlx_put_pixel(game->img, x, y++, color_floor);

// 		x++;
// 	}
// }
