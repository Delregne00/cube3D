/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

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
		map[i] = malloc(ft_strlen(line) + 1);
		if (!map[i])
		{
			free_map_partial(map, i);
			return (NULL);
		}
		ft_strcpy(map[i], trim_whitespace(line));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	*map_size = i;
	return (map);
}

void	process_map(t_cube *cube, char *line, int fd)
{
	char	**map;
	int		map_size;

	map = copy_map_fixed(line, fd, &map_size);
	if (!map)
	{
		print_error(1, "Error allocating memory for map");
		exit(1);
	}
	map_to_struct(cube, map);
}

bool	process_single_line(t_cube *cube, char *line, char **expected, int i)
{
	if (i == 4 || i == 7)
	{
		process_empty_line(line);
	}
	else if (i < 4)
	{
		if (!process_texture_lines(cube, line, expected, i))
			return (false);
	}
	else
	{
		if (!process_rgb_lines(cube, line, expected, i))
			return (false);
	}
	return (true);
}

static void	init_expected_array(char **expected)
{
	expected[0] = "NO ";
	expected[1] = "SO ";
	expected[2] = "WE ";
	expected[3] = "EA ";
	expected[4] = "";
	expected[5] = "F ";
	expected[6] = "C ";
	expected[7] = "";
}

static bool	process_lines_loop(t_cube *cube, char **line,
		int fd, char **expected)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (!process_single_line(cube, *line, expected, i))
			return (false);
		free(*line);
		*line = get_next_line(fd);
		i++;
	}
	return (true);
}

bool	process_file(t_cube *cube, int fd)
{
	char	*expected[8];
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		print_error(1, "Is a empty map");
		return (false);
	}
	init_expected_array(expected);
	if (!process_lines_loop(cube, &line, fd, expected))
		return (false);
	process_map(cube, line, fd);
	return (true);
}

bool	validation_file(t_cube *cube, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(2, file, "Cannot open file");
		return (false);
	}
	if (!process_file(cube, fd))
		return (false);
	close(fd);
	return (true);
}
