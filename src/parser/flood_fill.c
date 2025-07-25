#include "cube.h"

bool    check_connectivity(t_map *map, bool **visited)
{
    int i;
    int j;
    int row_len;
    
    i = 0;
    while (i < map->filas)
    {
        row_len = ft_strlen(map->map[i]);
        j = 0;
        while (j < row_len)
        {
            if (is_transitable(map->map[i][j]) && !visited[i][j])
            {
                print_error(4, "Unconnected transitable space at", ft_itoa(i), ft_itoa(j), "");
                return (false);
            }
            j++;
        }
        i++;
    }
    return (true);
}

bool    valid_position(t_map *map, int x, int y)
{
    int row_len;

    if (x < 0 || x >= map->filas || y < 0)
        return (false);
    row_len = ft_strlen(map->map[x]);
    if (y >= row_len)
        return (false);
    if (map->map[x][y] == ' ' || map->map[x][y] == '\0') 
        return (false);
    return (true);
}

bool    map_border(t_map *map, int x, int y)
{
    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};
    int i;
    int nx, ny;

    i = 0;
    while(i < 4)
    {
        nx = x + dx[i]; 
        ny = y + dy[i];
        if (!valid_position(map, nx, ny))
            return (true);
        i++; 
    }
    return (false);
}

bool    start_flood_fill(t_map *map, int x, int y, bool **visited)
{
    if (!valid_position(map, x, y))
        return (true);
    if (visited[x][y])
        return (true);
    if (map->map[x][y] == '1')
        return (true);
    if (!is_valid_char(map->map[x][y]))
    {
        print_error(3, "Invalid char in map position", ft_itoa(x), ft_itoa(y));
        return (false);
    }
        if (is_transitable(map->map[x][y]) && map_border(map, x, y))
    {
        print_error(4, "Transitable space at border", "Position", ft_itoa(x), ft_itoa(y));
        return (false);
    }
    visited[x][y] = true;
    if (!start_flood_fill(map, x - 1, y, visited)) return (false);
    if (!start_flood_fill(map, x + 1, y, visited)) return (false);
    if (!start_flood_fill(map, x, y - 1, visited)) return (false);
    if (!start_flood_fill(map, x, y + 1, visited)) return (false);
    return (true);
}

bool    flood_fill(t_map *map)
{
    bool    **visited;
    int     start_x;
    int     start_y;
    bool    result;

    if (!map || !map->map)
    {
        print_error(1, "Map is NULL");
        return (false);
    }
    map_dimensions(map);
    visited = init_visited_matrix(map);
    if (!visited)
    {
        print_error(1, "Failed to allocate visited matrix");
        return (false);
    }
    if (!start_position(map, &start_x, &start_y))
    {   
        print_error(1, "No transitable spaces found in map");
        free_visited_matrix(visited, map->filas);
        return (true); 
    }
    result = start_flood_fill(map, start_x, start_y, visited);
    if (result)
        result = check_connectivity(map, visited);
    free_visited_matrix(visited, map->filas);
    return (result);
}