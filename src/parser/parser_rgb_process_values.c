/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_rgb_process_values.c						:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:56:36 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:56:36 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

static bool	is_valid_number(char *str)
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

bool	parse_rgb_values(char *rgb, char *line)
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
