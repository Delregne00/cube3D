/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_elements.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:54:51 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:54:51 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

bool	handle_empty_line(t_process_data *data)
{
	cleanup_previous_lines(data);
	data->previous_line = ft_strdup(data->line);
	data->previous_trimmed = ft_strdup("");
	free(data->trimmed);
	free(data->line);
	data->line = get_next_line(data->fd);
	return (true);
}

// Procesa elementos de textura
bool	process_texture_element(t_process_data *data, char *prefix, int index)
{
	int	prefix_len;
	int	cube_index;

	prefix_len = ft_strlen(prefix);
	cube_index = index;
	if (!data->found[index] && ft_strncmp(data->trimmed,
			prefix, prefix_len) == 0
		&& process_texture_lines(data->cube, data->trimmed, cube_index,
			data->collector))
	{
		data->found[index] = 1;
		return (true);
	}
	return (false);
}

bool	process_rgb_element(t_process_data *data, char *prefix, int index)
{
	int	prefix_len;
	int	cube_index;

	prefix_len = ft_strlen(prefix);
	if (index == 4)
		cube_index = 5;
	else
		cube_index = 6;
	if (!data->found[index] && ft_strncmp(data->trimmed,
			prefix, prefix_len) == 0
		&& process_rgb_lines(data->cube, data->trimmed, cube_index))
	{
		data->found[index] = 1;
		return (true);
	}
	return (false);
}

bool	handle_unknown_element(t_process_data *data)
{
	if (!data->previous_trimmed || ft_strlen(data->previous_trimmed) != 0)
	{
		print_error(1, "Map must be preceded by empty line");
		free(data->trimmed);
		free(data->line);
		cleanup_previous_lines(data);
		return (false);
	}
	*(data->last_line) = data->line;
	free(data->trimmed);
	return (true);
}

int	process_single_line(t_process_data *data)
{
	data->trimmed = trim_whitespace(data->line);
	if (!data->trimmed || ft_strlen(data->trimmed) == 0)
	{
		handle_empty_line(data);
		return (1);
	}
	if (process_known_elements(data))
	{
		cleanup_previous_lines(data);
		data->previous_line = ft_strdup(data->line);
		data->previous_trimmed = ft_strdup(data->trimmed);
		free(data->trimmed);
		free(data->line);
		data->line = get_next_line(data->fd);
		return (1);
	}
	if (handle_unknown_element(data))
		return (0);
	return (-1);
}
