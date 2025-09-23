/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 flood_fill.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:54:34 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:54:34 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

void	init_directions(int directions[4][2])
{
	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
}

static void	flood_fill_recursive(char **visited, t_map *map, int i, int j)
{
	int	directions[4][2];
	int	di;
	int	dj;
	int	k;

	init_directions(directions);
	if (i < 0 || i >= map->filas || j < 0)
		return ;
	if (!map->map[i] || j >= (int)ft_strlen(map->map[i]))
		return ;
	if (visited[i][j] == '1' || !is_transitable(map->map[i][j]))
		return ;
	visited[i][j] = '1';
	k = 0;
	while (k < 4)
	{
		di = i + directions[k][0];
		dj = j + directions[k][1];
		flood_fill_recursive(visited, map, di, dj);
		k++;
	}
}

bool	validate_adjacent_cell(t_map *map, int di, int dj)
{
	if (di < 0 || di >= map->filas || dj < 0)
		return (false);
	if (!map->map[di] || dj >= (int)ft_strlen(map->map[di]))
		return (false);
	if (map->map[di][dj] == ' ')
		return (false);
	if (!is_wall_or_transitable(map->map[di][dj]))
		return (false);
	return (true);
}

bool	flood_fill_validation(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = create_visited_map(map);
	if (!visited)
		return (false);
	flood_fill_recursive(visited, map, map->player_y, map->player_x);
	i = 0;
	while (i < map->filas)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (is_transitable(map->map[i][j]) && visited[i][j] != '1')
			{
				free_visited_map(visited, map->filas);
				return (false);
			}
			j++;
		}
		i++;
	}
	free_visited_map(visited, map->filas);
	return (true);
}

bool	flood_fill(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->filas)
	{
		j = 0;
		while (map->map[i] && map->map[i][j])
		{
			if (!check_adjacent_positions(map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!flood_fill_validation(map))
		return (false);
	return (true);
}
