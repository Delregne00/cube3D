#include "includes/cube.h"

int main(int argc, char **argv)
{
    t_cube	*cube;
	t_game	*game;
    
    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return (1);
    }
    cube = cube_init();
    if (!cube)
    {
        printf("Error: Failed to initialize cube\n");
        exit(1);
    }
    if (!parser(cube, argv[1]))
    {
        printf("Error: Parsing failed\n");
        cube_free(cube);
        exit(1);
    }
    printf("Parsing completed successfully!\n");
    print_parsed_data(cube);
	game = game_init(cube);

	cube_free(cube);
	free(game);
    return (0);
}