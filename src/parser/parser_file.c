/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_file.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:55:07 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:55:07 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "includes/cube.h"

bool	process_map_line(char **map, char *line, int index)
{
	int	len;

	if (!line)
		return (false);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	map[index] = malloc(len + 1);
	if (!map[index])
		return (false);
	ft_strncpy(map[index], line, len);
	map[index][len] = '\0';
	return (true);
}

char	**copy_map_fixed(char *first_line, int fd, int *map_size)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = allocate_map();
	if (!map)
		return (NULL);
	line = first_line;
	while (line && i < MAX_MAP_SIZE)
	{
		if (!process_map_line(map, line, i))
		{
			free_map_partial(map, i);
			free(line);
			return (NULL);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map[i] = NULL;
	*map_size = i;
	return (map);
}

void	process_map(t_cube *cube, char *line, int fd, t_collector **collector)
{
	char	**map;
	int		map_size;

	map = copy_map_fixed(line, fd, &map_size);
	if (!map)
	{
		print_error(1, "Error allocating memory for map");
		exit(1);
	}
	map_to_struct(cube, map, collector);
}

bool	process_elements(t_cube *cube, int fd, t_collector **collector,
	char **last_line)
{
	t_process_data	data;
	int				result;

	init_basic_params(&data, cube, fd);
	init_process_data(&data, collector, last_line);
	while (data.line)
	{
		result = process_single_line(&data);
		if (result == -1)
			return (false);
		if (result == 0)
			break ;
	}
	cleanup_previous_lines(&data);
	if (verify_all_elements_found(&data))
		return (true);
	print_error(1, "Missing or invalid elements");
	if (data.line)
		free(data.line);
	return (false);
}

bool	process_file(t_cube *cube, int fd, t_collector **collector)
{
	char	*line;
	bool	ok;

	line = NULL;
	ok = process_elements(cube, fd, collector, &line);
	if (!ok)
		return (false);
	process_map(cube, line, fd, collector);
	return (true);
}
