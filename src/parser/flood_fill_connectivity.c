/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 flood_fill_connectivity.c							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/02 17:08:45 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/02 17:08:45 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

bool	check_connectivity(t_map *map, bool **visited)
{
	int		i;
	int		j;
	int		row_len;
	char	*x_str;

	i = 0;
	while (i < map->filas)
	{
		row_len = ft_strlen(map->map[i]);
		j = 0;
		while (j < row_len)
		{
			if (is_transitable(map->map[i][j]) && !visited[i][j])
			{
				x_str = ft_itoa(i);
				print_error(3, "Unconnected transitable space at", x_str, "");
				free(x_str);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	valid_position(t_map *map, int x, int y)
{
	int	row_len;

	if (x < 0 || x >= map->filas || y < 0)
		return (false);
	row_len = ft_strlen(map->map[x]);
	if (y >= row_len)
		return (false);
	if (map->map[x][y] == ' ' || map->map[x][y] == '\0')
		return (false);
	return (true);
}

static bool	is_outside_map(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->filas || y < 0)
		return (true);
	if (y >= (int)ft_strlen(map->map[x]))
		return (true);
	return (false);
}

bool	check_adjacent_positions(t_map *map, int x, int y)
{
	int	directions[4][2];
	int	i;
	int	nx;
	int	ny;

	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	i = 0;
	while (i < 4)
	{
		nx = x + directions[i][0];
		ny = y + directions[i][1];
		if (!is_outside_map(map, nx, ny) && map->map[nx][ny] == ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	start_flood_fill(t_map *map, int x, int y, bool **visited)
{
	if (!valid_position(map, x, y))
		return (true);
	if (visited[x][y])
		return (true);
	if (map->map[x][y] == '1')
		return (true);
	if (!validate_char_and_border(map, x, y))
		return (false);
	visited[x][y] = true;
	return (flood_fill_recursive(map, x, y, visited));
}
