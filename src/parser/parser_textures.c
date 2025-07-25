#include "cube.h"

char	*trim_whitespace(char *str)
{
	char	*end;

	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
		end--;
	end[1] = '\0';
	return (str);
}

void	process_empty_line(char *line)
{
	int	i;

	i = 0;
	line = trim_whitespace(line);
	while (line[i])
	{
		if (ft_isprint(line[i]))
		{
			print_error(3, "Line", line, "Must be empty");
			exit(1);
		}
		i++;
	}
}

bool	process_textures(t_cube *cube, char *line, int i)
{
	char	*expected[5] = {".xpm", ".bmp", ".png", ".jpg", ".jpeg"};
	int		j;
	bool	found;
	char	*clean_line;

	j = 0;
	found = false;
	clean_line = trim_whitespace(line);
	while (j < 5)
	{
		if (ft_strnstr(clean_line, expected[j], ft_strlen(clean_line)))
		{
			if (!validate_perimisons_exist(clean_line))
				return (false);
			found = true;
			break;
		}
		j++;
	}
	if (!found)
	{
		print_error(2, clean_line, "Not valid termination");
		return (false);
	}
	cube->data->textures[i] = ft_strdup(clean_line);
	if (!cube->data->textures[i])
	{
		print_error(1, "Memory allocation failed");
		return (false);
	}
	return(true);
}

bool	parse_line(t_cube *cube, char *line, char *expected, int len, int i, bool (*proces)(t_cube *, char *, int))
{
	if (ft_strncmp(line, expected, len) != 0)
	{
		print_error(4, "In line", ft_itoa(i + 1), "Expected", expected);
		free(line);
        return (false);
	}
	else
	{
		if (!proces(cube, line + len, i))
        	return (false);
		return (true);
	}
}

bool process_texture_lines(t_cube *cube, char *line, char **expected, int i)
{
	line = trim_whitespace(line);
	if (!parse_line(cube, line, expected[i], ft_strlen(expected[i]), i, process_textures))
		return (false);
	return (true);
}