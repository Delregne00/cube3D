/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	ptr_print(void **ptr, char *msg)
{
	if (!ptr || !*ptr)
		return ;
	fprintf(stderr, "%s %p: %s\n", msg, *ptr, (char *)*ptr);
}

void	freer(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	if (*ptr == (void *)0xDEADBEEF)
	{
		return ;
	}
	free(*ptr);
	*ptr = (void *)0xDEADBEEF;
}

void	print_msg(const char *msg)
{
	if (msg && *msg)
		if (write(2, msg, ft_strlen(msg)) == -1)
    		perror("write error");
	if (write(2, "\n", 1) == -1)
    	perror("write error");
}

// void	exit_program(t_collector **collector, const char *msg, bool should_exit)
// {
// 	collector_cleanup(collector);
// 	if (msg && *msg)
// 		print_msg(msg);
// 	if (should_exit)
// 		exit(EXIT_FAILURE);
// }

void	exit_program(t_collector **collector, const char *msg, bool should_exit, void *mlx)
{
	collector_cleanup(collector, mlx);
	if (msg && *msg)
		print_msg(msg);
	if (should_exit)
		exit(EXIT_FAILURE);
}
