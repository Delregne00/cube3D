/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_map_utils.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/02 18:00:15 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/02 18:00:15 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

void	assign_floor_color(t_cube *cube, char **rgb_parts)
{
	int		j;
	char	*trimmed;

	j = 0;
	while (j < 3)
	{
		trimmed = trim_whitespace(rgb_parts[j]);
		cube->data->f_color[j] = ft_atoi(trimmed);
		free(trimmed);
		j++;
	}
}

void	assign_ceiling_color(t_cube *cube, char **rgb_parts)
{
	int		j;
	char	*trimmed;

	j = 0;
	while (j < 3)
	{
		trimmed = trim_whitespace(rgb_parts[j]);
		cube->data->c_color[j] = ft_atoi(trimmed);
		free(trimmed);
		j++;
	}
}

void	free_rgb_parts(char **rgb_parts)
{
	int	j;

	j = 0;
	while (rgb_parts[j])
	{
		free(rgb_parts[j]);
		j++;
	}
	free(rgb_parts);
}

bool	validate_map_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
			{
				print_error(3, "Invalid character in map",
					"Line", ft_itoa(i + 1));
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
