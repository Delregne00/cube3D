#include "cube.h"

// void	print_map(char **map)
// {
//     int i = 0;
    
//     if (!map)
//         return;
    
//     while (map[i])
//     {
//         printf("%s\n", map[i]);
//         i++;
//     }
// }

void	print_map(t_map *map)
{
    int i;

	if (!map)
		return ;
	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	printf("\n");
}

void	print_parsed_data(t_cube *cube)
{
    int i;
    
    char *directions[4] = {"NO", "SO", "WE", "EA"};
    i = 0;
    while (i < 4)
    {
        if (cube->data->textures[i])
            printf("  %-3s: %s\n", directions[i], cube->data->textures[i]);
        else
            printf("  %-3s: [NOT SET]\n", directions[i]);
        i++;
    }
    if (cube->data->f_color[0] != -1)
        printf("  Floor (F):   RGB(%d, %d, %d)\n", 
               cube->data->f_color[0], 
               cube->data->f_color[1], 
               cube->data->f_color[2]);
    else
        printf("  Floor (F):   [NOT SET]\n");
        
    if (cube->data->c_color[0] != -1)
        printf("  Ceiling (C): RGB(%d, %d, %d)\n", 
               cube->data->c_color[0], 
               cube->data->c_color[1], 
               cube->data->c_color[2]);
    else
        printf("  Ceiling (C): [NOT SET]\n");
    if (cube->map)
    {
        // i = 0;
        // while (cube->map->map[i])
        // {
        //     printf("%s\n", cube->map->map[i]);
        //     i++;
        // }
		print_map(cube->map);
    }
    else
        printf("  [NOT SET]\n");
}

void print_error(int n, ...)
{
    va_list args;

    ft_putstr_fd("Cube 3D: ", STDERR_FILENO);
    va_start(args, n);
    while (n-- > 0)
    {
        ft_putstr_fd(va_arg(args, char*), STDERR_FILENO);
        if (n > 0)
            ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putstr_fd(".\n", STDERR_FILENO);
    va_end(args);
}

void free_map(t_map *map)
{
    int i = 0;
    
    if (!map)
        return;
    
    while (map->map[i])
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
}

char **allocate_map(void)
{
    char **map;
    
    map = malloc(sizeof(char *) * (MAX_MAP_SIZE + 1));
    return (map);
}

void free_map_partial(char **map, int size)
{
    int i = 0;
    
    if (!map)
        return;
    
    while (i < size)
    {
        if (map[i])
            free(map[i]);
        i++;
    }
    free(map);
}