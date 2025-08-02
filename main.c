#include "includes/cube.h"

int main(int argc, char **argv)
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
	//TODO: guardar cube a collector
    cube = cube_init();
    if (!cube)
    {
		//TODO: usar exit_program i buidar collector
		printf("Error: Failed to initialize cube\n");
        exit(1);
    }
    if (!parser(cube, argv[1]))
    {
		//TODO: usar exit_program i buidar collector
		printf("Error: Parsing failed\n");
		cube_free(cube);
		exit(1);
    }
	printf("Parsing completed successfully!\n");
	print_parsed_data(cube);
	game = game_init(cube, &collector);

	//TODO: no usar free i buidar collector
	cube_free(cube);
	free(game);
	collector_cleanup(&collector);
	return (EXIT_SUCCESS);
}