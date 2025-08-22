/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delregne <delregne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:00:00 by delregne          #+#    #+#             */
/*   Updated: 2025/08/22 08:22:29 by delregne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void raycasting(t_game *game)
{
    int x;
    t_ray ray;
    
    if (!validate_game_data(game))
        return;
        
    init_cache(game);
    display_fps();
    
    x = 0;
    while (x < game->width)
    {
        cast_single_ray(game, &ray, x);
        x++;
    }
}

bool validate_game_data(t_game *game)
{
    if (!game || !game->cube || !game->cube->map)
        return false;
    return true;
}

void init_cache(t_game *game)
{
    if (!g_cache.initialized)
        init_render_cache(game);
}

void display_fps(void)
{
    static int frame_count = 0;
    static time_t last_time = 0;
    time_t current_time;
    
    current_time = time(NULL);
    frame_count++;
    
    if (current_time > last_time)
    {
        printf("FPS: %d\n", frame_count);
        frame_count = 0;
        last_time = current_time;
    }
}

void cast_single_ray(t_game *game, t_ray *ray, int x)
{
    init_ray(game, ray, x);
    calc_step_and_side_dist(game, ray);
    perform_dda(game, ray);
    calc_wall_height(game, ray);
    draw_column_textured(game, ray, x);
}