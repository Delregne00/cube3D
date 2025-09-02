/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/02 17:09:07 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/02 17:09:07 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

char	*trim_whitespace(char *str)
{
	char	*end;

	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		end--;
	end[1] = '\0';
	return (str);
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
