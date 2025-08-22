#include "cube.h"

bool	is_valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'S'
		|| c == 'E' || c == '1' || c == ' ');
}

bool	is_transitable(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

void	free_visited_matrix(bool **visited, int filas)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < filas)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

bool	**init_visited_matrix(t_map *map)
{
	bool	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(bool *) * map->filas);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->filas)
	{
		visited[i] = malloc(sizeof(bool) * map->max_columnas);
		if (!visited[i])
		{
			free_visited_matrix(visited, i);
			return (NULL);
		}
		j = 0;
		while (j < map->max_columnas)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (visited);
}

bool	start_position(t_map *map, int *start_x, int *start_y)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	while (i < map->filas)
	{
		j = 0;
		row_len = ft_strlen(map->map[i]);
		while (j < row_len)
		{
			if (is_transitable(map->map[i][j]))
			{
				*start_x = i;
				*start_y = j;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}
