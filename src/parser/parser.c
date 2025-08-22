#include "cube.h"

bool	validate_extension(char *file, int size, char *extension)
{
	int	len;

	len = ft_strlen(file);
	if (len < size)
		return (false);
	if (ft_strcmp(file + (len - size), extension) != 0)
	{
		print_error(4, file, "Not valid extension.", "Only accept", extension);
		return (false);
	}
	return (true);
}

bool	validate_extensions(char *file)
{
	int		len;
	int		size;
	int		i;
	char	*extension[6];

	extension[0] = ".xpm";
	extension[1] = ".bmp";
	extension[2] = ".png";
	extension[3] = ".jpg";
	extension[4] = ".jpeg";
	extension[5] = NULL;
	len = ft_strlen(file);
	i = 0;
	while (extension[i])
	{
		size = ft_strlen(extension[i]);
		if (len >= size)
		{
			if (ft_strcmp(file + (len - size), extension[i]) == 0)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	file_content(char *file, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		print_error(2, file, "Is empty");
		close(fd);
		return (false);
	}
	free(line);
	return (true);
}

bool	validate_perimisons_exist(char *file)
{
	int	fd;

	if (!file)
	{
		print_error(2, "Bad arguments", "Need a map");
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			print_error(2, file, "File no exist");
		else if (errno == EACCES)
			print_error(2, file, "Permission denied");
		else
			print_error(2, file, "Error to open");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	parser(t_cube *cube, char *file)
{
	if (!validate_perimisons_exist(file) || !validate_extension(file, 4, ".cub")
		|| !validation_file(cube, file) || !validate_map(cube->map))
		return (false);
	return (true);
}
