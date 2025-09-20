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

bool	validate_rgb_format(char *line)
{
	int		i;
	int		comma_count;
	bool	after_comma;

	i = 0;
	comma_count = 0;
	after_comma = false;
	while (line[i])
	{
		if (line[i] == ',')
		{
			comma_count++;
			after_comma = true;
			if (i > 0 && line[i - 1] == ' ')
			{
				print_error(2, line, "No spaces allowed before comma in RGB");
				return (false);
			}
		}
		else if (line[i] == ' ')
		{
			if (after_comma)
			{
				print_error(2, line, "No spaces allowed after comma in RGB");
				return (false);
			}
		}
		else if (line[i] >= '0' && line[i] <= '9')
		{
			after_comma = false;
		}
		else
		{
			print_error(3, line, "Invalid character in RGB", &line[i]);
			return (false);
		}
		i++;
	}
	if (comma_count != 2)
	{
		print_error(2, line, "RGB must have exactly 2 commas");
		return (false);
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
	bool	result;

	clean_line = trim_whitespace(line);
	if (!validate_rgb_format(clean_line))
	{
		free(clean_line);
		return (false);
	}
	rgb_parts = ft_split(clean_line, ',');
	if (!rgb_parts)
	{
		print_error(2, line, "Invalid RGB values");
		free(clean_line);
		return (false);
	}
	result = validate_rgb_values(cube, rgb_parts, line);
	if (!result)
	{
		free_rgb_parts(rgb_parts);
		free(clean_line);
		return (false);
	}
	if (i == 5)
		assign_floor_color(cube, rgb_parts);
	else if (i == 6)
		assign_ceiling_color(cube, rgb_parts);
	free_rgb_parts(rgb_parts);
	free(clean_line);
	return (true);
}

bool process_rgb_lines(t_cube *cube, char *line, int i)
{
    char *trimmed_line;
    int prefix_len;
    bool ok;
    trimmed_line = trim_whitespace(line);
    if (!trimmed_line)
        return false;
    prefix_len = (i == 5 || i == 6) ? 2 : 0;
    if (prefix_len && ft_strncmp(trimmed_line, (i==5?"F ":"C "), prefix_len) != 0)
    {
        print_error(2, "Expected format not found", (i==5?"F ":"C "));
        free(trimmed_line);
        return false;
    }
    ok = process_rgb(cube, trimmed_line + prefix_len, i);
    free(trimmed_line);
    return ok;
}
