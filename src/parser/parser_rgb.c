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

bool	parse_rgb(char *rgb, char *line)
{
	int		value;
	char	*trimmed;

	trimmed = trim_whitespace(rgb);
	if (!is_valid_number(trimmed))
	{
		print_error(3, line, "Invalid RGB value", trimmed);
		return (false);
	}
	value = ft_atoi(trimmed);
	if (value < 0 || value > 255)
	{
		print_error(2, line, "RGB values must be between 0-255");
		return (false);
	}
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
	int		j;

	clean_line = trim_whitespace(line);
	rgb_parts = ft_split(clean_line, ',');
	if (!rgb_parts)
	{
		print_error(2, line, "Invalid RGB values");
		return (false);
	}
	if (!validate_rgb_values(cube, rgb_parts, line))
		return (false);
	if (i == 5)
	{
		j = 0;
		while (j < 3)
		{
			cube->data->f_color[j] = ft_atoi(trim_whitespace(rgb_parts[j]));
			j++;
		}
	}
	else if (i == 6) 
	{
		j = 0;
		while (j < 3)
		{
			cube->data->c_color[j] = ft_atoi(trim_whitespace(rgb_parts[j]));
			j++;
		}
	}
	j = 0;
	while (rgb_parts[j])
	{
		free(rgb_parts[j]);
		j++;
	}
	free(rgb_parts);
	return (true);
}

bool	process_rgb_lines(t_cube *cube, char *line, char **expected, int i)
{
	line = trim_whitespace(line);
	if(!parse_line(cube, line, expected[i], ft_strlen(expected[i]), i, process_rgb))
		return (false);
	return (true);
}