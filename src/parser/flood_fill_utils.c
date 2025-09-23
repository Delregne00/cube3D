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

bool	is_transitable(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

bool	is_wall_or_transitable(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'S'
		|| c == 'E' || c == '1');
}

bool	check_adjacent_positions(t_map *map, int i, int j)
{
	int	directions[4][2];
	int	di;
	int	dj;
	int	k;

	if (!is_transitable(map->map[i][j]))
		return (true);
	init_directions(directions);
	k = 0;
	while (k < 4)
	{
		di = i + directions[k][0];
		dj = j + directions[k][1];
		if (!validate_adjacent_cell(map, di, dj))
			return (false);
		k++;
	}
	return (true);
}

char	**create_visited_map(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * (map->filas + 1));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->filas)
	{
		visited[i] = malloc(ft_strlen(map->map[i]) + 1);
		if (!visited[i])
			return (NULL);
		j = 0;
		while (map->map[i][j])
		{
			visited[i][j] = '0';
			j++;
		}
		visited[i][j] = '\0';
		i++;
	}
	visited[map->filas] = NULL;
	return (visited);
}

void	free_visited_map(char **visited, int filas)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < filas)
	{
		if (visited[i])
			free(visited[i]);
		i++;
	}
	free(visited);
}
