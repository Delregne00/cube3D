/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_map.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/02 17:09:02 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/02 17:09:02 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "includes/cube.h"

void	map_to_struct(t_cube *cube, char **map, t_collector **collector)
{
	int	i;
	int	len;
	int	max_len;

	if (!cube || !cube->map || !map)
		return ;
	i = 0;
	while (map[i])
		i++;
	cube->map->filas = i;
	cube->map->map = map;
	collector_append(collector, map, RES_MALLOC, NULL);
	i = 0;
	while (map[i])
		collector_append(collector, map[i++], RES_MALLOC, NULL);
	max_len = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i++]);
		if (len > max_len)
			max_len = len;
	}
	cube->map->max_columnas = max_len;
}

void	map_dimensions(t_map *map)
{
	int	columnas;
	int	filas;
	int	i;
	int	max_columnas;

	if (!map || !map->map)
		return ;
	filas = 0;
	while (map->map[filas])
		filas++;
	map->filas = filas;
	max_columnas = 0;
	i = 0;
	while (map->map[i])
	{
		columnas = ft_strlen(map->map[i]);
		if (columnas > max_columnas)
			max_columnas = columnas;
		i++;
	}
	map->max_columnas = max_columnas;
}

static void	scan_map_for_player(t_map *game_map, int *player_count)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (game_map->map[i])
	{
		j = 0;
		while (game_map->map[i][j])
		{
			if (game_map->map[i][j] == 'N' || game_map->map[i][j] == 'S' ||
				game_map->map[i][j] == 'E' || game_map->map[i][j] == 'W')
			{
				(*player_count)++;
				game_map->player_x = j;
				game_map->player_y = i;
				game_map->player_dir = game_map->map[i][j];
			}
			j++;
		}
		i++;
	}
}

static bool	find_player_position(t_map *game_map, int *player_count)
{
	if (!game_map || !game_map->map || !player_count)
		return (false);
	scan_map_for_player(game_map, player_count);
	if (*player_count == 0)
	{
		print_error(1, "No player position found in map");
		return (false);
	}
	if (*player_count > 1)
	{
		print_error(1, "Multiple player positions found in map");
		return (false);
	}
	return (true);
}

bool	validate_map(t_map *map)
{
	int	player_count;

	if (!map)
	{
		print_error(1, "Map is NULL");
		return (false);
	}
	if (!validate_map_characters(map->map))
		return (false);
	if (!find_player_position(map, &player_count))
		return (false);
	if (!flood_fill(map))
		return (false);
	printf("Map validation: OK (Player count: %d)\n", player_count);
	return (true);
}
