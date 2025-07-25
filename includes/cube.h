#ifndef	CUBE_H
#define CUBE_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdarg.h>
# include "libraries/libft/libft.h"
# include "libraries/MLX42/include/MLX42/MLX42.h"

//Macros
#define MAX_MAP_SIZE 100

//structs

typedef struct s_map
{
    char    **map;
    int     filas;
    int     max_columnas;
}           t_map;

typedef struct  s_data
{
    char    **textures;
    int     f_color[3]; 
    int     c_color[3];  
}           t_data; 

typedef struct  s_cube
{
    t_data  *data;
    mlx_t   *mlx;
    t_map   *map;          
}           t_cube;

// Init functions
t_cube    *init(void);
void      free_cube(t_cube *cube);

//Parsing functions
bool    parser(t_cube *cube, char *file);
bool    validation_file(t_cube *cube, char *file);
bool    validate_perimisons_exist(char *file);
bool    process_rgb_lines(t_cube *cube, char *line, char **expected, int i);
bool    process_texture_lines(t_cube *cube, char *line, char **expected, int i);
bool    parse_line(t_cube *cube, char *line, char *expected, int len, int i, bool (*proces)(t_cube *, char *, int));
bool    process_rgb(t_cube *cube, char *line, int i);
bool    process_textures(t_cube *cube, char *line, int i);
void    map_to_struct(t_cube *cube, char **map);
void    map_dimensions(t_map *map);
bool    validate_map(t_map *map);
bool    flood_fill(t_map *map);

// Flood fill functions
bool    is_valid_char(char c);
bool    is_transitable(char c);
bool    valid_position(t_map *map, int x, int y);
bool    map_border(t_map *map, int x, int y);
bool    **init_visited_matrix(t_map *map);
void    free_visited_matrix(bool **visited, int filas);
bool    start_position(t_map *map, int *start_x, int *start_y);
bool    start_flood_fill(t_map *map, int x, int y, bool **visited);
bool    check_connectivity(t_map *map, bool **visited);

/*parsing utils*/
void    print_error(int n, ...);
void    print_map(char **map);
void    free_map(t_map *map);
char    **allocate_map(void);
void    free_map_partial(char **map, int size);
char    *trim_whitespace(char *str);
void    process_empty_line(char *line);
void    print_parsed_data(t_cube *cube);


#endif