#include "cube.h"

t_data *cube_data_init(void)
{
    t_data *data;
    int i;
    
    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data->textures = malloc(5 * sizeof(char *));
    if (!data->textures)
    {
        free(data);
        return (NULL);
    }
    i = 0;
    while (i < 5)
    {
        data->textures[i] = NULL;
        i++;
    }
    i = 0;
    while (i < 3)
    {
        data->f_color[i] = -1;
        data->c_color[i] = -1;
        i++;
    }
    return (data);
}

t_map *cube_map_init(void)
{
    t_map *map;
    
    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->map = NULL;
    map->filas = 0;
    map->max_columnas = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
    
    return (map);
}


t_cube *cube_init(void)
{
    t_cube *cube;
    
    cube = malloc(sizeof(t_cube));
    if (!cube)
        return (NULL);
    cube->data = cube_data_init();
    if (!cube->data)
    {
        free(cube);
        return (NULL);
    }
    cube->map = cube_map_init();
    if (!cube->map)
    {
        if (cube->data->textures)
        {
            int i = 0;
            while (i < 5)
            {
                if (cube->data->textures[i])
                    free(cube->data->textures[i]);
                i++;
            }
            free(cube->data->textures);
        }
        free(cube->data);
        free(cube);
        return (NULL);
    }
    // cube->mlx = NULL; 
    return (cube);
}

void cube_free(t_cube *cube)
{
    int i;
    
    if (!cube)
        return;
    
    if (cube->data)
    {
        if (cube->data->textures)
        {
            i = 0;
            while (i < 5)
            {
                if (cube->data->textures[i])
                    free(cube->data->textures[i]);
                i++;
            }
            free(cube->data->textures);
        }
        free(cube->data);
    }
    free(cube);
}