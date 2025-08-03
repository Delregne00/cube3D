/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/07/26 09:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

mlx_texture_t	*select_texture(t_game *game, int side, int ray_dir_x, int ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (game->cube->tex_west);
		else
			return (game->cube->tex_east);
	}
	else
	{
		if (ray_dir_y > 0)
			return (game->cube->tex_north);
		else
			return (game->cube->tex_south);
	}
}


static void	draw_texture_column(t_ray *r, t_game *game, int x, int h)
{
	int				y;
	mlx_texture_t	*tex;
	uint8_t			*pixels;
	int				texX;
	int				texY;
	uint32_t		color;
	double			wallX;
	int				line_height;

	y = r->drawStart;
	tex = select_texture(game, r->side, r->rayDirX, r->rayDirY);
	if (!tex || !tex->pixels)
		return ;
	pixels = tex->pixels;
	line_height = r->lineHeight;

	if (r->side == 0)
		wallX = game->player.y + r->perpWallDist * r->rayDirY;
	else
		wallX = game->player.x + r->perpWallDist * r->rayDirX;
	wallX -= floor(wallX);

	texX = (int)(wallX * tex->width);
	if (texX < 0 || texX >= (int)tex->width)
		return ;

	while (y < r->drawEnd && y < h)
	{
		texY = ((y - r->drawStart) * tex->height) / line_height;
		if (texY >= 0 && texY < (int)tex->height)
			color = *((uint32_t *)(pixels + (texY * tex->width + texX) * 4));
		else
			color = 0xFF00FF00;
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

static void	calc_wall_distance(t_ray *r)
{
	if (r->side == 0)
		r->perpWallDist = r->sideDistX - r->deltaDistX;
	else
		r->perpWallDist = r->sideDistY - r->deltaDistY;
}

static void	calc_draw_limits(t_ray *r, int h)
{
	r->lineHeight = (int)(h / r->perpWallDist);
	r->drawStart = -r->lineHeight / 2 + h / 2;
	r->drawEnd = r->lineHeight / 2 + h / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	if (r->drawEnd >= h)
		r->drawEnd = h - 1;
}

static void	calc_hit(t_ray *r, t_game *game)
{
	while (r->hit == 0)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapY >= 0 && r->mapX >= 0 &&
			r->mapY < game->cube->map->filas &&
			r->mapX < (int)ft_strlen(game->cube->map->map[r->mapY]) &&
			game->cube->map->map[r->mapY][r->mapX] == '1')
			r->hit = 1;
	}
}

static void	calc_step(t_ray *r, t_game *game)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (game->player.x - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - game->player.x) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (game->player.y - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - game->player.y) * r->deltaDistY;
	}
}

static int	check_ray_bounds(t_ray *r, t_game *game)
{
	if (r->mapX < 0 || r->mapY < 0)
		return (0);
	if (r->mapY >= game->cube->map->filas)
		return (0);
	if (r->mapX >= game->cube->map->max_columnas)
		return (0);
	return (1);
}

static void	init_ray(t_ray *r, t_game *game, int x, int w)
{
	double	cameraX;

	cameraX = 2 * x / (double)w - 1;
	r->rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
	r->rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
	r->mapX = (int)game->player.x;
	r->mapY = (int)game->player.y;
	r->deltaDistX = fabs(1 / r->rayDirX);
	r->deltaDistY = fabs(1 / r->rayDirY);
	r->hit = 0;
	r->side = 0;
}

void	render_raycast(t_game *game)
{
	int		w;
	int		h;
	int		x;

	w = WIN_W;
	h = WIN_H;
	x = 0;
	if (!game->cube->tex_north || !game->cube->tex_north->pixels ||
		!game->cube->tex_south || !game->cube->tex_south->pixels ||
		!game->cube->tex_west || !game->cube->tex_west->pixels ||
		!game->cube->tex_east || !game->cube->tex_east->pixels ||
		!game->img)
	{
		// if (write(2, "Error: textures no carregades o game->img és NULL\n", 51) == -1)
		// 	perror("write error");
		print_msg("Error: textures no carregades o game->img és NULL");
		return ;
	}
	while (x < w)
	{
		t_ray	r;

		init_ray(&r, game, x, w);
		if (check_ray_bounds(&r, game) == 0)
			break ;
		calc_step(&r, game);
		calc_hit(&r, game);
		calc_wall_distance(&r);
		calc_draw_limits(&r, h);
		draw_texture_column(&r, game, x, h);
		x++;
	}
}




// void render_raycast(t_game *game)
// {
// 	int w = WIN_W;
// 	int h = WIN_H;

// 	printf("render_raycast in\n");
// 	if (!game->wall_tex || !game->wall_tex->pixels)
// 	{
// 		fprintf(stderr, "Error: wall texture no carregada\n");
// 		return;
// 	}
// 	if (!game->img)
// 	{
// 		fprintf(stderr, "Error: game->img és NULL\n");
// 		return;
// 	}

// 	for (int x = 0; x < w; x++)
// 	{
// //		printf("step: mapX=%d, mapY=%d, char=%c\n", mapX, mapY, game->cube->map->map[mapY][mapX]);
// 		double cameraX = 2 * x / (double)w - 1;
// 		double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
// 		double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

// 		int mapX = (int)game->player.x;
// 		int mapY = (int)game->player.y;

// 		double sideDistX;
// 		double sideDistY;

// 		double deltaDistX = fabs(1 / rayDirX);
// 		double deltaDistY = fabs(1 / rayDirY);
// 		double perpWallDist;

// 		int stepX;
// 		int stepY;

// 		int hit = 0;
// 		int side;

// 		side = 0;
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (game->player.x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (game->player.y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
// 		}
// 		// printf("render_raycast 1\n");

// 		if (mapX < 0 || mapY < 0 || mapY >= game->cube->map->filas || mapX >= game->cube->map->max_columnas)
// 		{
// 			printf("mapX or mapY out of bounds: (%d, %d)\n", mapX, mapY);
// 			break;
// 		}

// 		while (hit == 0)
// 		{

// 			if (mapX < 0 || mapY < 0 || mapY >= game->cube->map->filas || mapX >= (int)ft_strlen(game->cube->map->map[mapY]))
// 			{
// 				printf("Accés fora del mapa! mapX=%d mapY=%d\n", mapX, mapY);
// 				break;
// 			}

// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (game->cube->map->map[mapY][mapX] == '1')
// 				hit = 1;
// 		}
// 		// printf("render_raycast 2\n");

// 		if (side == 0)
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);

// 		int lineHeight = (int)(h / perpWallDist);
// 		int drawStart = -lineHeight / 2 + h / 2;
// 		int drawEnd = lineHeight / 2 + h / 2;

// 		if (drawStart < 0) drawStart = 0;
// 		if (drawEnd >= h) drawEnd = h - 1;

// 		// for (int y = drawStart; y < drawEnd; y++)
// 		// {
// 		// 	int texY = ((y - drawStart) * game->wall_tex->height) / lineHeight;
// 		// 	int texX = (int)(game->wall_tex->width * (side == 0 ?
// 		// 				game->player.y + perpWallDist * rayDirY :
// 		// 				game->player.x + perpWallDist * rayDirX));
// 		// 	texX = ((texX * game->wall_tex->width) / 64) % game->wall_tex->width;

// 		// 	uint8_t *tex = game->wall_tex->pixels;
// 		// 	uint32_t color = *((uint32_t *)(tex + (texY * game->wall_tex->width + texX) * 4));
// 		// 	// mlx_put_pixel(game->img, x, y, color);
// 		// 	mlx_put_pixel(game->img, x, y, 0xFF0000FF); // Vermell
// 		// }
// 		for (int y = drawStart; y < drawEnd; y++)
// 		{
// 			mlx_texture_t *tex = select_texture(game, side, rayDirX, rayDirY);
// 			uint8_t *pixels = tex->pixels;
// 			int texX = (int)(game->wall_tex->width * (side == 0 ?
// 						game->player.y + perpWallDist * rayDirY :
// 						game->player.x + perpWallDist * rayDirX));
// 			int texY = ((y - drawStart) * tex->height) / lineHeight;
// 			uint32_t color = *((uint32_t *)(pixels + (texY * tex->width + texX) * 4));
// 			mlx_put_pixel(game->img, x, y, color);		}
// 	}
// 	printf("render_raycast out\n");
// }

// static void put_pixel(t_game *game, int x, int y, uint32_t color)
// {
// 	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
// 		return;

// 	uint32_t *pixels = (uint32_t *)game->addr;
// 	pixels[y * WIN_W + x] = color;
// }


// void render(void *param)
// {
// 	t_game *game = (t_game *)param;

// 	// Netegem la imatge (exemple: color fosc)
// 	memset(game->addr, 0, WIN_W * WIN_H * sizeof(uint32_t));

// 	// Exemples de píxels:
// 	for (int x = 0; x < WIN_W; x++)
// 		for (int y = 0; y < WIN_H / 2; y++)
// 			put_pixel(game, x, y, 0xFF87CEEB); // blau cel

// 	for (int x = 0; x < WIN_W; x++)
// 		for (int y = WIN_H / 2; y < WIN_H; y++)
// 			put_pixel(game, x, y, 0xFF228B22); // verd gespa

// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// }
