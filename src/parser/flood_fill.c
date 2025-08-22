/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	check_connectivity(t_map *map, bool **visited)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	while (i < map->filas)
	{
		row_len = ft_strlen(map->map[i]);
		j = 0;
		while (j < row_len)
		{
			if (is_transitable(map->map[i][j]) && !visited[i][j])
			{
				print_error(4, "Unconnected transitable space at",
					ft_itoa(i), ft_itoa(j), "");
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

static bool	check_adjacent_positions(t_map *map, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	dx[0] = -1;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = -1;
	dy[3] = 1;
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (!valid_position(map, nx, ny))
			return (true);
		i++;
	}
	return (false);
}

bool	map_border(t_map *map, int x, int y)
{
	return (check_adjacent_positions(map, x, y));
}

static bool	validate_char_and_border(t_map *map, int x, int y)
{
	if (!is_valid_char(map->map[x][y]))
	{
		print_error(3, "Invalid char in map position", ft_itoa(x), ft_itoa(y));
		return (false);
	}
	if (is_transitable(map->map[x][y]) && map_border(map, x, y))
	{
		print_error(4, "Transitable space at border",
			"Position", ft_itoa(x), ft_itoa(y));
		return (false);
	}
	return (true);
}

static bool	flood_fill_recursive(t_map *map, int x, int y, bool **visited)
{
	if (!start_flood_fill(map, x - 1, y, visited))
		return (false);
	if (!start_flood_fill(map, x + 1, y, visited))
		return (false);
	if (!start_flood_fill(map, x, y - 1, visited))
		return (false);
	if (!start_flood_fill(map, x, y + 1, visited))
		return (false);
	return (true);
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

static bool	initialize_flood_fill(t_map *map, bool ***visited)
{
	if (!map || !map->map)
	{
		print_error(1, "Map is NULL");
		return (false);
	}
	map_dimensions(map);
	*visited = init_visited_matrix(map);
	if (!*visited)
	{
		print_error(1, "Failed to allocate visited matrix");
		return (false);
	}
	return (true);
}

static bool	execute_flood_fill(t_map *map, bool **visited)
{
	int		start_x;
	int		start_y;
	bool	result;

	if (!start_position(map, &start_x, &start_y))
	{
		print_error(1, "No transitable spaces found in map");
		free_visited_matrix(visited, map->filas);
		return (true);
	}
	result = start_flood_fill(map, start_x, start_y, visited);
	if (result)
		result = check_connectivity(map, visited);
	return (result);
}

bool	flood_fill(t_map *map)
{
	bool	**visited;
	bool	result;

	if (!initialize_flood_fill(map, &visited))
		return (false);
	result = execute_flood_fill(map, visited);
	free_visited_matrix(visited, map->filas);
	return (result);
}
