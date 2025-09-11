/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	parse_rgb(char *rgb, char *line)
{
	int		value;
	char	*trimmed;

	trimmed = trim_whitespace(rgb);
	if (!is_valid_number(trimmed))
	{
		print_error(3, line, "Invalid RGB value", trimmed);
		free(trimmed);
		return (false);
	}
	value = ft_atoi(trimmed);
	if (value < 0 || value > 255)
	{
		print_error(2, line, "RGB values must be between 0-255");
		free(trimmed);
		return (false);
	}
	free(trimmed);
	return (true);
}

bool	validate_rgb_values(t_cube *cube, char **rgb_parts, char *original_line)
{
	int	i;

	i = 0;
	(void)cube;
	while (rgb_parts[i])
		i++;
	if (i != 3)
	{
		print_error(2, original_line, "RGB must have exactly 3 values");
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (!parse_rgb(rgb_parts[i], original_line))
			return (false);
		i++;
	}
	return (true);
}

bool	process_rgb(t_cube *cube, char *line, int i)
{
	char	**rgb_parts;
	char	*clean_line;

	clean_line = trim_whitespace(line);
	rgb_parts = ft_split(clean_line, ',');
	if (!rgb_parts)
	{
		print_error(2, line, "Invalid RGB values");
		free(clean_line);
		return (false);
	}
	if (!validate_rgb_values(cube, rgb_parts, line))
	{
		free(clean_line);
		return (false);
	}
	if (i == 5)
		assign_floor_color(cube, rgb_parts);
	else if (i == 6)
		assign_ceiling_color(cube, rgb_parts);
	free(clean_line);
	free_rgb_parts(rgb_parts);
	return (true);
}

bool	process_rgb_lines(t_cube *cube, char *line, char **expected, int i)
{
	line = trim_whitespace(line);
	if (!parse_line(cube, line, expected[i], ft_strlen(expected[i])))
	{
		free(line);
		return (false);
	}
	if (!process_rgb(cube, line + ft_strlen(expected[i]), i))
	{
		free(line);
		return (false);
	}
	free(line);
	return (true);
}
