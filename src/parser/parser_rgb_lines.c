/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/20 18:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*get_rgb_prefix(int i)
{
	if (i == 5)
		return ("F ");
	else if (i == 6)
		return ("C ");
	return (NULL);
}

static int	get_prefix_length(int i)
{
	if (i == 5 || i == 6)
		return (2);
	return (0);
}

static bool	rgb_format_validation(char *trimmed_line, int i, int prefix_len)
{
	char	*expected_prefix;

	if (!prefix_len)
		return (true);
	expected_prefix = get_rgb_prefix(i);
	if (ft_strncmp(trimmed_line, expected_prefix, prefix_len) != 0)
	{
		print_error(2, "Expected format not found", expected_prefix);
		return (false);
	}
	return (true);
}

bool	process_rgb_lines(t_cube *cube, char *line, int i)
{
	char	*trimmed_line;
	int		prefix_len;
	bool	validation_result;
	bool	process_result;

	trimmed_line = trim_whitespace(line);
	if (!trimmed_line)
		return (false);
	prefix_len = get_prefix_length(i);
	validation_result = rgb_format_validation(trimmed_line, i, prefix_len);
	if (!validation_result)
	{
		free(trimmed_line);
		return (false);
	}
	process_result = process_rgb(cube, trimmed_line + prefix_len, i);
	free(trimmed_line);
	return (process_result);
}
