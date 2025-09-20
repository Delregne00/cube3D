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

char **copy_map_fixed(char *first_line, int fd, int *map_size)
{
	char **map;
	char *line;
	int i;
	char *trimmed;
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
		trimmed = trim_whitespace(line);
		ft_strcpy(map[i], trimmed);
		i++;
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map[i] = NULL;
	*map_size = i;
	return (map);
}

void process_map(t_cube *cube, char *line, int fd, t_collector **collector)
{
	char **map;
	int map_size;
	map = copy_map_fixed(line, fd, &map_size);
	if (!map)
	{
		print_error(1, "Error allocating memory for map");
		exit(1);
	}
	map_to_struct(cube, map, collector);
}

bool	process_elements(t_cube *cube, int fd, t_collector **collector, char **last_line)
{
	int		found[6];
	int		i;
	char	*line;
	char	*trimmed;
	char	*previous_line;
	char	*previous_trimmed;

	for (i = 0; i < 6; i++)
		found[i] = 0;
	line = get_next_line(fd);
	previous_line = NULL;
	previous_trimmed = NULL;

	while (line)
	{
		trimmed = trim_whitespace(line);

		if (!trimmed || ft_strlen(trimmed) == 0)
		{
			if (previous_line)
				free(previous_line);
			if (previous_trimmed)
				free(previous_trimmed);
			previous_line = ft_strdup(line);
			previous_trimmed = ft_strdup("");
			free(trimmed);
			free(line);
			line = get_next_line(fd);
			continue;
		}

		if (!found[0] && ft_strncmp(trimmed, "NO ", 3) == 0
			&& process_texture_lines(cube, trimmed, 0, collector))
			found[0] = 1;
		else if (!found[1] && ft_strncmp(trimmed, "SO ", 3) == 0
			&& process_texture_lines(cube, trimmed, 1, collector))
			found[1] = 1;
		else if (!found[2] && ft_strncmp(trimmed, "WE ", 3) == 0
			&& process_texture_lines(cube, trimmed, 2, collector))
			found[2] = 1;
		else if (!found[3] && ft_strncmp(trimmed, "EA ", 3) == 0
			&& process_texture_lines(cube, trimmed, 3, collector))
			found[3] = 1;
		else if (!found[4] && ft_strncmp(trimmed, "F ", 2) == 0
			&& process_rgb_lines(cube, trimmed, 5))
			found[4] = 1;
		else if (!found[5] && ft_strncmp(trimmed, "C ", 2) == 0
			&& process_rgb_lines(cube, trimmed, 6))
			found[5] = 1;
		else
		{
			if (!previous_trimmed || ft_strlen(previous_trimmed) != 0)
			{
				print_error(1, "Map must be preceded by empty line");
				free(trimmed);
				free(line);
				if (previous_line)
					free(previous_line);
				if (previous_trimmed)
					free(previous_trimmed);
				return (false);
			}
			*last_line = line;
			free(trimmed);
			break;
		}
		if (previous_line)
			free(previous_line);
		if (previous_trimmed)
			free(previous_trimmed);
		previous_line = ft_strdup(line);
		previous_trimmed = ft_strdup(trimmed);
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}

	if (previous_line)
		free(previous_line);
	if (previous_trimmed)
		free(previous_trimmed);

	if (found[0] && found[1] && found[2] && found[3] && found[4] && found[5])
		return (true);
	print_error(1, "Missing or invalid elements");
	if (line)
		free(line);
	return (false);
}

bool process_file(t_cube *cube, int fd, t_collector **collector)
{
	char *line;
	bool ok;
	line = NULL;
	ok = process_elements(cube, fd, collector, &line);
	if (!ok)
		return false;
	process_map(cube, line, fd, collector);
	return true;
}

bool validation_file(t_cube *cube, char *file, t_collector **collector)
{
	int fd;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(2, file, "Cannot open file");
		return (false);
	}
	if (!process_file(cube, fd, collector))
		return (false);
	close(fd);
	return (true);
}
