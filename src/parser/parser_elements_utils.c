/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_elements_utils.c							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:54:59 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:54:59 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

void	init_basic_params(t_process_data *data, t_cube *cube, int fd)
{
	data->cube = cube;
	data->fd = fd;
	data->line = get_next_line(fd);
	data->previous_line = NULL;
	data->previous_trimmed = NULL;
}

void	init_process_data(t_process_data *data, t_collector **collector,
	char **last_line)
{
	int	i;

	data->collector = collector;
	data->last_line = last_line;
	i = 0;
	while (i < 6)
		data->found[i++] = 0;
}

void	cleanup_previous_lines(t_process_data *data)
{
	if (data->previous_line)
	{
		free(data->previous_line);
		data->previous_line = NULL;
	}
	if (data->previous_trimmed)
	{
		free(data->previous_trimmed);
		data->previous_trimmed = NULL;
	}
}

bool	verify_all_elements_found(t_process_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!data->found[i])
			return (false);
		i++;
	}
	return (true);
}

bool	process_known_elements(t_process_data *data)
{
	if (process_texture_element(data, "NO ", 0))
		return (true);
	if (process_texture_element(data, "SO ", 1))
		return (true);
	if (process_texture_element(data, "WE ", 2))
		return (true);
	if (process_texture_element(data, "EA ", 3))
		return (true);
	if (process_rgb_element(data, "F ", 4))
		return (true);
	if (process_rgb_element(data, "C ", 5))
		return (true);
	return (false);
}
