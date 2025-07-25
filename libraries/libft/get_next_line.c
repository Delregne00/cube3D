#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int buffer_read;
	static int	buffer_pos;
	int	i = 0;
	char	line[70000];
	if (fd < 0||  BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		if (buffer[buffer_pos] == '\n')
		{
		line[i++] = buffer[buffer_pos++];
		break ;
		}
		 line[i++] = buffer[buffer_pos++];
	}
	line[i] = '\0';
	if (i == 0 && buffer_read <= 0)
		return NULL;
	return (ft_strdup(line));
}