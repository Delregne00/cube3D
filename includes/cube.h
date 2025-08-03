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
# include <math.h>
# include "libraries/libft/libft.h"
# include "libraries/MLX42/include/MLX42/MLX42.h"

//Macros
# define MAX_MAP_SIZE 100
# define WIN_W 1280
# define WIN_H 720
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */

typedef struct s_collector
{
	void				*ptr;
	struct s_collector	*next;
}	t_collector;

typedef struct s_map
{
	char    **map;
	int     filas;
	int     max_columnas;
}           t_map;

typedef struct s_data
{
	char	**textures;		// [0]=NO, [1]=SO, [2]=WE, [3]=EA
	int		f_color[3];		// Floor RGB
	int		c_color[3];		// Ceiling RGB
}	t_data;

typedef struct s_cube
{
	t_data			*data;
	t_map			*map;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
}	t_cube;

typedef struct s_player {
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_game {
	t_cube			*cube;
	t_player		player;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				width;
	int				height;
	// mlx_texture_t	*tex_north;
	// mlx_texture_t	*tex_south;
	// mlx_texture_t	*tex_west;
	// mlx_texture_t	*tex_east;
	t_collector		*collector;
} t_game;

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}	t_ray;

/* ========================================================================== */
/*                           UTILITY FUNCTIONS                                */
/* ========================================================================== */

/* util/utils.c */
void	ptr_print(void **ptr, char *msg);
void	freer(void **ptr);
void	print_msg(const char *msg);
void	exit_program(t_collector **collector, const char *msg,
			bool should_exit);


/* ========================================================================== */
/*                           MEMORY MANAGEMENT                                */
/* ========================================================================== */

/* util/collector.c */
bool	collector_contains(t_collector *collector, void *ptr);
void	collector_remove_ptr(t_collector **collector, void *ptr);
void	collector_cleanup(t_collector **collector);
void	collector_append(t_collector **collector, void *ptr);


/* ========================================================================== */
/*                           INIT FUNCTIONS                                   */
/* ========================================================================== */
/* init/cube_init.c */
t_cube    *cube_init(void);
void      cube_free(t_cube *cube);

/* init/game_init.c */
t_game	*game_init(t_cube *cube, t_collector **collector);

/* Parsing functions */
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

/* Flood fill functions */
bool    is_valid_char(char c);
bool    is_transitable(char c);
bool    valid_position(t_map *map, int x, int y);
bool    map_border(t_map *map, int x, int y);
bool    **init_visited_matrix(t_map *map);
void    free_visited_matrix(bool **visited, int filas);
bool    start_position(t_map *map, int *start_x, int *start_y);
bool    start_flood_fill(t_map *map, int x, int y, bool **visited);
bool    check_connectivity(t_map *map, bool **visited);

/* parsing utils */
void    print_error(int n, ...);
void    print_map(char **map);
void    free_map(t_map *map);
char    **allocate_map(void);
void    free_map_partial(char **map, int size);
char    *trim_whitespace(char *str);
void    process_empty_line(char *line);
void    print_parsed_data(t_cube *cube);


/* ========================================================================== */
/*                           RENDER FUNCTIONS                                 */
/* ========================================================================== */
/* raycasting/render.c */
void	render(void *param);
void	render_raycast(t_game *game);

/* raycasting/textures.c */
mlx_texture_t	*load_texture(const char *path);
int				load_textures(t_cube *cube);

/* raycasting/render_utils.c */
void	print_cube_data(t_cube *cube);

#endif