#include "cube.h"

void	print_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	printf("\n");
}

void	print_error(int n, ...)
{
	va_list	args;

	ft_putstr_fd("Cube 3D: ", STDERR_FILENO);
	va_start(args, n);
	while (n-- > 0)
	{
		ft_putstr_fd(va_arg(args, char *), STDERR_FILENO);
		if (n > 0)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(".\n", STDERR_FILENO);
	va_end(args);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

char	**allocate_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * (MAX_MAP_SIZE + 1));
	return (map);
}

void	free_map_partial(char **map, int size)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < size)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}
