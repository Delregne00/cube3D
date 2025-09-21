/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_next_line.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/21 16:06:33 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/09/21 16:06:33 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*get_gnl_instance(void)
{
	static t_gnl	gnl = {{0}, 0, 0};

	return (&gnl);
}

static int	fill_buffer_and_read_char(t_gnl *gnl, int fd, char *c)
{
	if (gnl->buffer_pos >= gnl->buffer_read)
	{
		gnl->buffer_read = read(fd, gnl->buffer, BUFFER_SIZE);
		gnl->buffer_pos = 0;
		if (gnl->buffer_read <= 0)
			return (0);
	}
	*c = gnl->buffer[gnl->buffer_pos++];
	return (1);
}

static char	*build_line(t_gnl *gnl, int fd)
{
	char	line[70000];
	char	c;
	int		i;

	i = 0;
	while (1)
	{
		if (!fill_buffer_and_read_char(gnl, fd, &c))
			break ;
		line[i++] = c;
		if (c == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0 && gnl->buffer_read <= 0)
		return (NULL);
	return (ft_strdup(line));
}

char	*get_next_line(int fd)
{
	t_gnl	*gnl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl = get_gnl_instance();
	return (build_line(gnl, fd));
}
