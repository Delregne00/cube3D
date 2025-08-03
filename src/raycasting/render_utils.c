/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/08/03 11:05:00 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cube.h"

void	print_textures_and_colors(t_cube *cube)
{
	char	buffer[1024];

	print_msg("Textures:");
	sprintf(buffer, "NO: %s", cube->data->textures[0]);
	print_msg(buffer);
	sprintf(buffer, "SO: %s", cube->data->textures[1]);
	print_msg(buffer);
	sprintf(buffer, "WE: %s", cube->data->textures[2]);
	print_msg(buffer);
	sprintf(buffer, "EA: %s", cube->data->textures[3]);
	print_msg(buffer);

	print_msg("\nColors:");
	sprintf(buffer, "Floor: %d,%d,%d", cube->data->f_color[0],
			cube->data->f_color[1], cube->data->f_color[2]);
	print_msg(buffer);
	sprintf(buffer, "Ceiling: %d,%d,%d", cube->data->c_color[0],
			cube->data->c_color[1], cube->data->c_color[2]);
	print_msg(buffer);
}

// void	print_cube_data(t_cube *cube)
// {
// 	char	buffer[64];
// 	int		len;

// 	//TODO: veure parser_utils/print_parsed_data(), fa el mateix

// 	// write(1, "Textures:\n", 10);
// 	print_msg("Textures:");
// 	write(1, "NO: ", 4);
// 	write(1, cube->data->textures[0], ft_strlen(cube->data->textures[0]));
// 	write(1, "\nSO: ", 5);
// 	write(1, cube->data->textures[1], ft_strlen(cube->data->textures[1]));
// 	write(1, "\nWE: ", 5);
// 	write(1, cube->data->textures[2], ft_strlen(cube->data->textures[2]));
// 	write(1, "\nEA: ", 5);
// 	write(1, cube->data->textures[3], ft_strlen(cube->data->textures[3]));
// 	write(1, "\n\nColors:\n", 10);

// 	len = sprintf(buffer, "F: %d,%d,%d\n", cube->data->f_color[0], cube->data->f_color[1], cube->data->f_color[2]);
// 	write(1, buffer, len);
// 	len = sprintf(buffer, "C: %d,%d,%d\n", cube->data->c_color[0], cube->data->c_color[1], cube->data->c_color[2]);
// 	write(1, buffer, len);
// }

