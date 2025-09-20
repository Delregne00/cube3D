/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/20 20:30:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

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

static bool	validate_texture_file(char *clean_line)
{
	if (!check_texture_extension(clean_line))
	{
		print_error(2, clean_line, "Not valid termination");
		return (false);
	}
	if (!validate_perimisons_exist(clean_line))
		return (false);
	return (true);
}

static bool	assign_texture(t_cube *cube, char *clean_line, int i,
	t_collector **collector)
{
	cube->data->textures[i] = ft_strdup(clean_line);
	if (!cube->data->textures[i])
	{
		print_error(1, "Memory allocation failed");
		return (false);
	}
	collector_append(collector, cube->data->textures[i], RES_MALLOC, NULL);
	return (true);
}

bool	process_textures(t_cube *cube, char *line, int i,
	t_collector **collector)
{
	char	*clean_line;
	bool	validation_result;
	bool	assign_result;

	clean_line = trim_whitespace(line);
	if (!clean_line)
	{
		print_error(1, "Memory allocation failed for trimming");
		return (false);
	}
	validation_result = validate_texture_file(clean_line);
	if (!validation_result)
	{
		free(clean_line);
		return (false);
	}
	assign_result = assign_texture(cube, clean_line, i, collector);
	free(clean_line);
	if (!assign_result)
		return (false);
	return (true);
}
