/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/20 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	process_empty_line(char *line)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	trimmed_line = trim_whitespace(line);
	while (trimmed_line[i])
	{
		if (ft_isprint(trimmed_line[i]))
		{
			print_error(3, "Line", trimmed_line, "Must be empty");
			free(trimmed_line);
			exit(1);
		}
		i++;
	}
	free(trimmed_line);
}

static char	*get_texture_prefix(int i)
{
	if (i == 0)
		return ("NO ");
	else if (i == 1)
		return ("SO ");
	else if (i == 2)
		return ("WE ");
	else if (i == 3)
		return ("EA ");
	return (NULL);
}

static bool	validate_texture_format(char *trimmed_line, int i)
{
	char	*expected_prefix;
	int		prefix_len;

	expected_prefix = get_texture_prefix(i);
	if (!expected_prefix)
		return (false);
	prefix_len = 3;
	if (ft_strncmp(trimmed_line, expected_prefix, prefix_len) != 0)
	{
		print_error(2, "Expected format not found", expected_prefix);
		return (false);
	}
	return (true);
}

bool	process_texture_lines(t_cube *cube, char *line, int i,
	t_collector **collector)
{
	char	*trimmed_line;
	bool	validation_result;
	bool	process_result;

	trimmed_line = trim_whitespace(line);
	if (!trimmed_line)
		return (false);
	validation_result = validate_texture_format(trimmed_line, i);
	if (!validation_result)
	{
		free(trimmed_line);
		return (false);
	}
	process_result = process_textures(cube, trimmed_line + 3, i, collector);
	if (!process_result)
	{
		free(trimmed_line);
		return (false);
	}
	free(trimmed_line);
	return (true);
}
