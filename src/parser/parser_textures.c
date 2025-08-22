/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
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

void	process_empty_line(char *line)
{
	int	i;

	i = 0;
	line = trim_whitespace(line);
	while (line[i])
	{
		if (ft_isprint(line[i]))
		{
			print_error(3, "Line", line, "Must be empty");
			exit(1);
		}
		i++;
	}
}

static bool	check_texture_extension(char *clean_line)
{
	if (ft_strnstr(clean_line, ".xpm", ft_strlen(clean_line)))
		return (true);
	if (ft_strnstr(clean_line, ".bmp", ft_strlen(clean_line)))
		return (true);
	if (ft_strnstr(clean_line, ".png", ft_strlen(clean_line)))
		return (true);
	if (ft_strnstr(clean_line, ".jpg", ft_strlen(clean_line)))
		return (true);
	if (ft_strnstr(clean_line, ".jpeg", ft_strlen(clean_line)))
		return (true);
	return (false);
}

bool	process_textures(t_cube *cube, char *line, int i)
{
	char	*clean_line;

	clean_line = trim_whitespace(line);
	if (!check_texture_extension(clean_line))
	{
		print_error(2, clean_line, "Not valid termination");
		return (false);
	}
	if (!validate_perimisons_exist(clean_line))
		return (false);
	cube->data->textures[i] = ft_strdup(clean_line);
	if (!cube->data->textures[i])
	{
		print_error(1, "Memory allocation failed");
		return (false);
	}
	return (true);
}

bool	parse_line(t_cube *cube, char *line, char *expected, int len)
{
	(void)cube;
	if (ft_strncmp(line, expected, len) != 0)
	{
		print_error(2, "Expected format not found", expected);
		free(line);
		return (false);
	}
	return (true);
}

bool	process_texture_lines(t_cube *cube, char *line, char **expected, int i)
{
	line = trim_whitespace(line);
	if (!parse_line(cube, line, expected[i], ft_strlen(expected[i])))
		return (false);
	if (!process_textures(cube, line + ft_strlen(expected[i]), i))
		return (false);
	return (true);
}
