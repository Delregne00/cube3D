/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarranz <acarranz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2025/09/11 11:15:41 by acarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int	main(int argc, char **argv)
{
	t_cube		*cube;
	t_game		*game;
	t_collector	*collector;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	collector = NULL;
	cube = cube_init(&collector);
	if (!cube)
		exit_program(&collector, "Error: Failed to initialize cube",
			EXIT_FAILURE, NULL);
	collector_append(&collector, cube, RES_MALLOC, NULL);
	if (!parser(cube, argv[1], &collector))
		exit_program(&collector, "Error: Parsing failed", EXIT_FAILURE, NULL);
	printf("Parsing completed successfully!\n");
	game = game_init(cube, &collector);
	if (!game)
		exit_program(&collector, "Error: Failed to initialize game",
			EXIT_FAILURE, NULL);
	collector_cleanup(&collector, game->mlx);
	printf("Surt de cub3D sense errors!\n");
	return (EXIT_SUCCESS);
}
