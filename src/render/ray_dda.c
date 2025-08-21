/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delregne <delregne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/08/21 09:41:07 by delregne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void perform_dda(t_game *game, t_ray *ray)
{
    ray->hit = 0;
    
    while (ray->hit == 0)
    {
        dda_step(ray);
        if (check_bounds(game, ray))
            break;
        if (check_wall_hit(game, ray))
            ray->hit = 1;
    }
}

void dda_step(t_ray *ray)
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
}

bool check_bounds(t_game *game, t_ray *ray)
{
    int max_cols;
    int max_rows;
    
    max_cols = game->cube->map->max_columnas;
    max_rows = game->cube->map->filas;
    
    if (ray->mapX < 0 || ray->mapY < 0)
    {
        ray->hit = 1;
        return true;
    }
    if (ray->mapY >= max_rows || ray->mapX >= max_cols)
    {
        ray->hit = 1;
        return true;
    }
    return false;
}

bool check_wall_hit(t_game *game, t_ray *ray)
{
    char **map;
    
    map = game->cube->map->map;
    return (map[ray->mapY][ray->mapX] == '1');
}