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

bool	validate_char_and_border(t_map *map, int x, int y)
{
	char	*x_str;
	char	*y_str;

	if (!is_valid_char(map->map[x][y]))
	{
		x_str = ft_itoa(x);
		y_str = ft_itoa(y);
		print_error(3, "Invalid char in map position", x_str, y_str);
		free(x_str);
		free(y_str);
		return (false);
	}
	if (is_transitable(map->map[x][y]) && check_adjacent_positions(map, x, y))
	{
		x_str = ft_itoa(x);
		y_str = ft_itoa(y);
		print_error(4, "Transitable space at border", "Position", x_str, y_str);
		free(x_str);
		free(y_str);
		return (false);
	}
	return (true);
}

bool	flood_fill_recursive(t_map *map, int x, int y, bool **visited)
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

bool	initialize_flood_fill(t_map *map, bool ***visited)
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

bool	execute_flood_fill(t_map *map, bool **visited)
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
