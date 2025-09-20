/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process_elements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:00:00 by acarranz          #+#    #+#             */
/*   Updated: 2025/09/20 20:35:46 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_found_array(int *found)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		found[i] = 0;
		i++;
	}
}

static void	free_previous_vars(char **prev_line, char **prev_trimmed)
{
	if (*prev_line)
		free(*prev_line);
	if (*prev_trimmed)
		free(*prev_trimmed);
}

static void	set_previous_empty(char **prev_line, char **prev_trimmed, char *line)
{
	free_previous_vars(prev_line, prev_trimmed);
	*prev_line = ft_strdup(line);
	*prev_trimmed = ft_strdup("");
}

static void	set_previous_content(char **prev_line, char **prev_trimmed,
		char *line, char *trimmed)
{
	free_previous_vars(prev_line, prev_trimmed);
	*prev_line = ft_strdup(line);
	*prev_trimmed = ft_strdup(trimmed);
}

static bool	process_texture_element(t_cube *cube, char *trimmed,
		t_collector **collector, int *found)
{
	if (!found[0] && ft_strncmp(trimmed, "NO ", 3) == 0
		&& process_texture_lines(cube, trimmed, 0, collector))
	{
		found[0] = 1;
		return (true);
	}
	if (!found[1] && ft_strncmp(trimmed, "SO ", 3) == 0
		&& process_texture_lines(cube, trimmed, 1, collector))
	{
		found[1] = 1;
		return (true);
	}
	if (!found[2] && ft_strncmp(trimmed, "WE ", 3) == 0
		&& process_texture_lines(cube, trimmed, 2, collector))
	{
		found[2] = 1;
		return (true);
	}
	if (!found[3] && ft_strncmp(trimmed, "EA ", 3) == 0
		&& process_texture_lines(cube, trimmed, 3, collector))
	{
		found[3] = 1;
		return (true);
	}
	return (false);
}

static bool	process_color_element(t_cube *cube, char *trimmed, int *found)
{
	if (!found[4] && ft_strncmp(trimmed, "F ", 2) == 0
		&& process_rgb_lines(cube, trimmed, 5))
	{
		found[4] = 1;
		return (true);
	}
	if (!found[5] && ft_strncmp(trimmed, "C ", 2) == 0
		&& process_rgb_lines(cube, trimmed, 6))
	{
		found[5] = 1;
		return (true);
	}
	return (false);
}

static bool	process_config_line(t_cube *cube, char *trimmed,
		t_collector **collector, int *found)
{
	if (process_texture_element(cube, trimmed, collector, found))
		return (true);
	if (process_color_element(cube, trimmed, found))
		return (true);
	return (false);
}

static bool	validate_empty_before_map(char *prev_trimmed)
{
	if (!prev_trimmed || ft_strlen(prev_trimmed) != 0)
	{
		print_error(1, "Map must be preceded by empty line");
		return (false);
	}
	return (true);
}

static void	cleanup_all(char *trimmed, char *line,
		char *prev_line, char *prev_trimmed)
{
	free(trimmed);
	free(line);
	if (prev_line)
		free(prev_line);
	if (prev_trimmed)
		free(prev_trimmed);
}

static bool	all_elements_found(int *found)
{
	if (found[0] && found[1] && found[2] && found[3] && found[4] && found[5])
		return (true);
	return (false);
}

static void	handle_empty_line_process(char **previous_line, char **previous_trimmed,
		char *trimmed, char *line, int fd, char **next_line)
{
	set_previous_empty(previous_line, previous_trimmed, line);
	free(trimmed);
	free(line);
	*next_line = get_next_line(fd);
}

static bool	handle_map_start(char *previous_trimmed, char *trimmed,
		char *line, char **last_line)
{
	if (!validate_empty_before_map(previous_trimmed))
		return (false);
	*last_line = line;
	free(trimmed);
	return (true);
}

static void	handle_successful_config(char **previous_line, char **previous_trimmed,
		char *line, char *trimmed, int fd, char **next_line)
{
	set_previous_content(previous_line, previous_trimmed, line, trimmed);
	free(trimmed);
	free(line);
	*next_line = get_next_line(fd);
}

static bool	finalize_processing(int *found, char **previous_line,
		char **previous_trimmed, char *line)
{
	free_previous_vars(previous_line, previous_trimmed);
	if (all_elements_found(found))
		return (true);
	print_error(1, "Missing or invalid elements");
	if (line)
		free(line);
	return (false);
}

bool	process_elements(t_cube *cube, int fd,
		t_collector **collector, char **last_line)
{
	int		found[6];
	char	*line;
	char	*trimmed;
	char	*previous_line;
	char	*previous_trimmed;

	init_found_array(found);
	line = get_next_line(fd);
	previous_line = NULL;
	previous_trimmed = NULL;
	while (line)
	{
		trimmed = trim_whitespace(line);
		if (!trimmed || ft_strlen(trimmed) == 0)
		{
			handle_empty_line_process(&previous_line, &previous_trimmed,
				trimmed, line, fd, &line);
			continue;
		}
		if (!process_config_line(cube, trimmed, collector, found))
		{
			if (!handle_map_start(previous_trimmed, trimmed, line, last_line))
			{
				cleanup_all(trimmed, line, previous_line, previous_trimmed);
				return (false);
			}
			break;
		}
		handle_successful_config(&previous_line, &previous_trimmed,
			line, trimmed, fd, &line);
	}
	return (finalize_processing(found, &previous_line, &previous_trimmed, line));
}
