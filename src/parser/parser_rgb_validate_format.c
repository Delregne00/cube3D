/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_rgb_validate_format.c						:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 14:56:30 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 14:56:30 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cube.h"

static bool	validate_rgb_char(char *line, int i, bool *after_comma)
{
	if (line[i] == ',')
	{
		*after_comma = true;
		if (i > 0 && line[i - 1] == ' ')
		{
			print_error(2, line, "No spaces allowed before comma in RGB");
			return (false);
		}
	}
	else if (line[i] == ' ')
	{
		if (*after_comma)
		{
			print_error(2, line, "No spaces allowed after comma in RGB");
			return (false);
		}
	}
	else if (line[i] >= '0' && line[i] <= '9')
		*after_comma = false;
	else
	{
		print_error(3, line, "Invalid character in RGB", &line[i]);
		return (false);
	}
	return (true);
}

bool	validate_rgb_format(char *line)
{
	int		i;
	int		comma_count;
	bool	after_comma;
	bool	char_valid;

	i = 0;
	comma_count = 0;
	after_comma = false;
	while (line[i])
	{
		if (line[i] == ',')
			comma_count++;
		char_valid = validate_rgb_char(line, i, &after_comma);
		if (!char_valid)
			return (false);
		i++;
	}
	if (comma_count != 2)
	{
		print_error(2, line, "RGB must have exactly 2 commas");
		return (false);
	}
	return (true);
}
