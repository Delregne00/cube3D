/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/06 10:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	set_north_direction(t_player *player)
{
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	player->plane_x = 0.66;
	player->plane_y = 0.0;
}

static void	set_south_direction(t_player *player)
{
	player->dir_x = 0.0;
	player->dir_y = 1.0;
	player->plane_x = -0.66;
	player->plane_y = 0.0;
}

static void	set_east_direction(t_player *player)
{
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
}

static void	set_west_direction(t_player *player)
{
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = -0.66;
}

void	player_set_direction(t_player *player, char direction)
{
	if (direction == 'N')
		set_north_direction(player);
	else if (direction == 'S')
		set_south_direction(player);
	else if (direction == 'E')
		set_east_direction(player);
	else if (direction == 'W')
		set_west_direction(player);
}
