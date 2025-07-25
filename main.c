#include "includes/cube.h"

int main(int argc, char **argv)
{
    t_cube *cube;
    
    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return (1);
    }
    cube = init();
    if (!cube)
    {
        printf("Error: Failed to initialize cube\n");
        exit(1);
    }
    if (!parser(cube, argv[1]))
    {
        printf("Error: Parsing failed\n");
        free_cube(cube);
        exit(1);
    }
    printf("Parsing completed successfully!\n");
    print_parsed_data(cube);
    free_cube(cube);
    return (0);
}