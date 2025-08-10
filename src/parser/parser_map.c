#include "cube.h"

void map_to_struct(t_cube *cube, char **map)
{
    int i;
    int len;
    int max_len;

    if (!cube || !cube->map || !map)
        return;
    i = 0;
    while (map[i])
        i++;
    cube->map->filas = i;
    cube->map->map = map;
    max_len = 0;
    i = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    cube->map->max_columnas = max_len;
}

void map_dimensions(t_map *map)
{
    int columnas;
    int filas;
    int i;
    int max_columnas;

    if (!map || !map->map)
        return;
    filas = 0;
    while (map->map[filas])
        filas++;
    map->filas = filas;
    max_columnas = 0;
    i = 0;
    while (map->map[i])
    {
        columnas = ft_strlen(map->map[i]);
        if (columnas > max_columnas)
            max_columnas = columnas;
        i++;
    }
    map->max_columnas = max_columnas;
}

bool validate_map_characters(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!is_valid_char(map[i][j]))
            {
                print_error(3, "Invalid character in map", "Line", ft_itoa(i + 1));
                return (false);
            }
            j++;
        }
        i++;
    }
    return (true);
}

// bool find_player_position(char **map, int *player_count)
// {
//     int i;
//     int j;

//     if (!map || !player_count)
//         return (false);

//     *player_count = 0;
//     i = 0;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j])
//         {
//             if (map[i][j] == 'N' || map[i][j] == 'S' ||
//                 map[i][j] == 'E' || map[i][j] == 'W')
//             {
//                 (*player_count)++;
//             }
//             j++;
//         }
//         i++;
//     }
//     if (*player_count == 0)
//     {
//         print_error(1, "No player position found in map");
//         return (false);
//     }
//     if (*player_count > 1)
//     {
//         print_error(1, "Multiple player positions found in map");
//         return (false);
//     }
//     return (true);
// }

static bool find_player_position(t_map *game_map, int *player_count)
{
    int i;
    int j;

    if (!game_map || !game_map->map || !player_count)
        return (false);

    *player_count = 0;
    i = 0;
    while (game_map->map[i])
    {
        j = 0;
        while (game_map->map[i][j])
        {
            if (game_map->map[i][j] == 'N' || game_map->map[i][j] == 'S' ||
                game_map->map[i][j] == 'E' || game_map->map[i][j] == 'W')
            {
                (*player_count)++;
                // Guardar la posición y dirección del jugador
                game_map->player_x = j;
                game_map->player_y = i;
                game_map->player_dir = game_map->map[i][j];
            }
            j++;
        }
        i++;
    }
    if (*player_count == 0)
    {
        print_error(1, "No player position found in map");
        return (false);
    }
    if (*player_count > 1)
    {
        print_error(1, "Multiple player positions found in map");
        return (false);
    }
    return (true);
}


bool validate_map(t_map *map)
{
    int     player_count;

    if (!map)
    {
        print_error(1, "Map is NULL");
        return (false);
    }
    if (!validate_map_characters(map->map))
        return (false);
    // if (!find_player_position(map->map, &player_count))
    if (!find_player_position(map, &player_count))
        return (false);
    if (!flood_fill(map))
        return (false);
    printf("Map validation: OK (Player count: %d)\n", player_count);
    return (true);
}