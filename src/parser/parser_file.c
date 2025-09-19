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
	char	*trimmed;

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
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (NULL);
		}
		trimmed = trim_whitespace(line);
		ft_strcpy(map[i], trimmed);
		i++;
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
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
		return ;
	}
	map_to_struct(cube, map, collector);
}

static bool	process_lines_loop(t_cube *cube, char **line,
		int fd, char **expected, t_collector **collector)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (i == 4 || i == 7)
		{
			process_empty_line(*line);
		}
		else if (i < 4)
		{
			if (!process_texture_lines(cube, *line, expected, i, collector))
			{
				if (*line)
					free(*line);
				while ((*line = get_next_line(fd)) != NULL)
					free(*line);
				return (false);
			}
		}
		else
		{
			if (!process_rgb_lines(cube, *line, expected, i))
			{
				if (*line)
					free(*line);
				while ((*line = get_next_line(fd)) != NULL)
					free(*line);
				return (false);
			}
		}
		free(*line);
		*line = get_next_line(fd);
		i++;
	}
	return (true);
}

bool	process_file(t_cube *cube, int fd, t_collector **collector)
{
	char	*expected[8];
	char	*line;

	expected[0] = "NO ";
	expected[1] = "SO ";
	expected[2] = "WE ";
	expected[3] = "EA ";
	expected[4] = "";
	expected[5] = "F ";
	expected[6] = "C ";
	expected[7] = "";
	line = get_next_line(fd);
	if (line == NULL)
	{
		print_error(1, "Is a empty map");
		return (false);
	}
	if (!process_lines_loop(cube, &line, fd, expected, collector))
		return (false);
	if (line)
		process_map(cube, line, fd, collector);
	return (true);
}

bool	validation_file(t_cube *cube, char *file, t_collector **collector)
{
	int		fd;
	bool	result;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(2, file, "Cannot open file");
		return (false);
	}
	result = process_file(cube, fd, collector);
	close(fd);
	return (result);
}
