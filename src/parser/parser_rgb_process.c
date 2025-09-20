/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/20 18:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	validate_rgb_values(t_cube *cube, char **rgb_parts,
	char *original_line)
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
		if (!parse_rgb_values(rgb_parts[i], original_line))
			return (false);
		i++;
	}
	return (true);
}

static void	assign_rgb_color(t_cube *cube, char **rgb_parts, int i)
{
	if (i == 5)
		assign_floor_color(cube, rgb_parts);
	else if (i == 6)
		assign_ceiling_color(cube, rgb_parts);
}

static bool	process_and_validate_rgb(t_cube *cube, char *clean_line,
	char *line, int i)
{
	char	**rgb_parts;
	bool	validation_result;

	rgb_parts = ft_split(clean_line, ',');
	if (!rgb_parts)
	{
		print_error(2, line, "Invalid RGB values");
		return (false);
	}
	validation_result = validate_rgb_values(cube, rgb_parts, line);
	if (!validation_result)
	{
		free_rgb_parts(rgb_parts);
		return (false);
	}
	assign_rgb_color(cube, rgb_parts, i);
	free_rgb_parts(rgb_parts);
	return (true);
}

bool	process_rgb(t_cube *cube, char *line, int i)
{
	char	*clean_line;
	bool	format_valid;
	bool	process_result;

	clean_line = trim_whitespace(line);
	if (!clean_line)
		return (false);
	format_valid = validate_rgb_format(clean_line);
	if (!format_valid)
	{
		free(clean_line);
		return (false);
	}
	process_result = process_and_validate_rgb(cube, clean_line, line, i);
	free(clean_line);
	return (process_result);
}
