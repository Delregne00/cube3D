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

void 	process_empty_line(char *line)
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

// Add this parameter to process_textures function signature
bool	process_textures(t_cube *cube, char *line, int i, t_collector **collector)
{
	char	*clean_line;

	clean_line = trim_whitespace(line);
	if (!clean_line)
	{
		print_error(1, "Memory allocation failed for trimming");
		return (false);
	}
	if (!check_texture_extension(clean_line))
	{
		print_error(2, clean_line, "Not valid termination");
		free(clean_line);
		return (false);
	}
	if (!validate_perimisons_exist(clean_line))
	{
		free(clean_line);
		return (false);
	}
	cube->data->textures[i] = ft_strdup(clean_line);
	if (!cube->data->textures[i])
	{
		free(clean_line);
		print_error(1, "Memory allocation failed");
		return (false);
	}
	// Add texture string to collector for proper cleanup
	collector_append(collector, cube->data->textures[i], RES_MALLOC, NULL);
	free(clean_line);
	return (true);
}

bool	parse_line(t_cube *cube, char *line, char *expected, int len)
{
	(void)cube;
	if (ft_strncmp(line, expected, len) != 0)
	{
		print_error(2, "Expected format not found", expected);
		return (false);
	}
	return (true);
}

bool process_texture_lines(t_cube *cube, char *line, int i, t_collector **collector)
{
    char *trimmed_line;
    int prefix_len;
    trimmed_line = trim_whitespace(line);
    if (!trimmed_line)
        return false;
    if (i == 0) prefix_len = 3;
    else if (i == 1) prefix_len = 3;
    else if (i == 2) prefix_len = 3;
    else if (i == 3) prefix_len = 3;
    else return false;
    if (ft_strncmp(trimmed_line, (i==0?"NO ":i==1?"SO ":i==2?"WE ":"EA "), prefix_len) != 0)
    {
        print_error(2, "Expected format not found", (i==0?"NO ":i==1?"SO ":i==2?"WE ":"EA "));
        free(trimmed_line);
        return false;
    }
    if (!process_textures(cube, trimmed_line + prefix_len, i, collector))
    {
        free(trimmed_line);
        return false;
    }
    free(trimmed_line);
    return true;
}
