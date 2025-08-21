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
# include <stdint.h>
# include <time.h>
# include "libraries/libft/libft.h"
// # include "libraries/MLX42/include/MLX42/MLX42.h"
# include "libraries/minilibx/mlx.h"

//Macros
# define MAX_MAP_SIZE 100
# define WIN_W 1920
# define WIN_H 1080
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

// Macros para el minimap
#define MINIMAP_SCALE 5     // Tamaño de cada celda del mapa
#define MINIMAP_OFFSET_X 20     // Posición X del minimap en la ventana
#define MINIMAP_OFFSET_Y 20     // Posición Y del minimap en la ventana
#define PLAYER_SIZE 3           // Tamaño del punto del jugador
#define PLAYER_DIR_LENGTH 15    // Longitud de la línea de dirección

// Colors minimap
// #define COLOR_WALL 0xFF0000FF   // Rojo para paredes
// #define COLOR_FLOOR 0xFFFFFFFF  // Blanco para suelo
// #define COLOR_PLAYER 0x00FF00FF // Verde para jugador
// #define COLOR_DIR 0x0000FFFF    // Azul para dirección
// Colors format RGB de minilibX (sense canal alpha)
#define COLOR_WALL 0xFF0000     // Rojo para paredes
#define COLOR_FLOOR 0xFFFFFF    // Blanco para suelo
#define COLOR_PLAYER 0x00FF00   // Verde para jugador
#define COLOR_DIR 0x0000FF      // Azul para dirección
#define COLOR_BLACK 0x000000    // Negro para fondo

// Macros tecles minilibX
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363


// Variables globals x estat de tecles
typedef struct s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
} t_keys;

/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */

typedef struct s_map
{
	char    **map;
	int     filas;
	int     max_columnas;
	int     player_x;
	int     player_y;
	char    player_dir;
}           t_map;

typedef struct s_data
{
	char	**textures;		// [0]=NO, [1]=SO, [2]=WE, [3]=EA
	int		f_color[3];		// Floor RGB
	int		c_color[3];		// Ceiling RGB
}	t_data;

typedef struct s_player {
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_texture
{
    void    *img;        // punter a la imatge MLX
    char    *addr;       // punter a la memòria de píxels
    int     width;       // amplada en píxels
    int     height;      // alçada en píxels
    int     bpp;         // bits per píxel
    int     line_len;    // bytes per línia
    int     endian;      // endianess (normalment 0)
}   t_texture;

// typedef struct s_cube
// {
//     t_data      *data;
//     t_map       *map;
//     mlx_image_t *tex_north;
//     mlx_image_t *tex_south;
//     mlx_image_t *tex_west;
//     mlx_image_t *tex_east;
// }   t_cube;

// typedef struct s_cube
// {
//     t_data  *data;
//     t_map   *map;
//     void    *tex_north;
//     void    *tex_south;
//     void    *tex_west;
//     void    *tex_east;
// }   t_cube;

typedef struct s_cube
{
    t_data      *data;
    t_map       *map;
    t_texture   tex_north;
    t_texture   tex_south;
    t_texture   tex_west;
    t_texture   tex_east;
}   t_cube;

// typedef struct s_game {
// 	t_cube			*cube;
// 	t_player		player;
// 	mlx_t           *mlx;
// 	mlx_image_t     *img;
// 	char			*addr;
// 	int				width;
// 	int				height;
// } t_game;

typedef struct s_game {
    t_cube  *cube;
    t_player player;
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_game;

// typedef struct s_collector
// {
// 	void				*ptr;
// 	struct s_collector	*next;
// }	t_collector;

typedef enum e_resource_type
{
	RES_MALLOC,
	RES_IMG,
	RES_WIN
}	t_resource_type;

typedef struct s_collector
{
	void				*ptr;
	t_resource_type		type;
	struct s_collector	*next;
}	t_collector;

typedef struct s_game_loop_param
{
    t_game       *game;
    t_collector  **collector;
} t_game_loop_param;

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

typedef struct s_render_cache {
    uint32_t    floor_color;
    uint32_t    ceil_color;
    double      sin_rot;
    double      cos_rot;
    t_texture   *tex_cache[4];  // Cache de texturas
    int         initialized;
} t_render_cache;


extern t_render_cache g_cache;

typedef struct s_column_data
{
    t_texture   *tex;
    uint32_t    *pixels;
    int         width;
    int         height;
    int         draw_start;
    int         draw_end;
    int         texX;
    double      step;
    double      texPos;
}   t_column_data;



/* ========================================================================== */
/*                           UTILITY FUNCTIONS                                */
/* ========================================================================== */

/* util/utils.c */
void	ptr_print(void **ptr, char *msg);
void	freer(void **ptr);
void	print_msg(const char *msg);
// void	exit_program(t_collector **collector, const char *msg,
// 			bool should_exit);
void	exit_program(t_collector **collector, const char *msg, 
			bool should_exit, void *mlx);

/* ========================================================================== */
/*                           MEMORY MANAGEMENT                                */
/* ========================================================================== */

/* util/collector.c */
bool	collector_contains(t_collector *collector, void *ptr);
void	collector_remove_ptr(t_collector **collector, void *ptr);
// void	collector_cleanup(t_collector **collector);
void	collector_cleanup(t_collector **collector, void *mlx);
// void	collector_append(t_collector **collector, void *ptr);
void	collector_append(t_collector **collector, void *ptr, 
			t_resource_type type, void *mlx);


/* ========================================================================== */
/*                           INIT FUNCTIONS                                   */
/* ========================================================================== */
/* init/cube_init.c */
t_cube	*cube_init(t_collector **collector);
void	cube_free(t_cube *cube);

/* init/game_init.c */
t_game	*game_init(t_cube *cube, t_collector **collector);
void player_init(t_game *game);

/* ========================================================================== */
/*                           PARSER FUNCTIONS                                 */
/* ========================================================================== */
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

/* parser/parser_utils.c */
void	print_map(t_map *map);
// void    print_map(char **map);
void    print_error(int n, ...);
void    free_map(t_map *map);
char    **allocate_map(void);
void    free_map_partial(char **map, int size);
char    *trim_whitespace(char *str);
void    process_empty_line(char *line);
void    print_parsed_data(t_cube *cube);

/* ========================================================================== */
/*                          MINIMAP FUNCTIONS                                 */
/* ========================================================================== */
void	render_minimap(t_game *game);
void	draw_map_grid(t_game *game);
void	draw_player(t_game *game);
void	draw_player_direction(t_game *game);
// void draw_square(t_game *game, int x, int y, int size, uint32_t color);
// void draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void	put_pixel_to_image(t_game *game, int x, int y, int color);


/* ========================================================================== */
/*                  PLAYER MOVEMENT FUNCTIONS                                 */
/* ========================================================================== */
/* minimap/input.c */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
// void	handle_input(t_game *game);
void	handle_input(t_game_loop_param *p);
// int		close_window(t_game *game);
int	close_window(t_game_loop_param *p);
// void	setup_hooks(t_game *game, t_game_loop_param *param);
void	hooks_setup(t_game_loop_param *p);

/* minimap/player_movement.c */
// void handle_input(t_game *game);
void	move_player(t_game *game, int direction);
void	strafe_player(t_game *game, int direction);
void	rotate_player(t_game *game, int direction);
bool	is_wall(t_game *game, double x, double y);

/* ========================================================================== */
/*                           RENDER FUNCTIONS                                 */
/* ========================================================================== */

/* render/raycasting.c */
void	raycasting(t_game *game);

/* render/render.c */
//void	render(void *param);
void	render_raycast(t_game *game);
uint32_t	rgb_to_color(int r, int g, int b);
void		put_pixel_safe(t_game *game, int x, int y, uint32_t color);
t_texture *select_texture(t_game *game, t_ray *ray);
uint32_t	get_texture_pixel(t_texture *tex, int texX, int texY);

/* render/textures.c */
int		tex_pixel_get(t_texture *tex, int x, int y);
// int		textures_load(t_cube *cube);
int		textures_load(t_game *game, t_collector **collector);

/* render/render_utils.c */
//void	print_cube_data(t_cube *cube);
void	print_textures_and_colors(t_cube *cube);
void init_ray(t_game *game, t_ray *ray, int x);
bool is_wall_fast(t_game *game, int map_x, int map_y);
void put_pixel_safe(t_game *game, int x, int y, uint32_t color);
uint32_t rgb_to_color(int r, int g, int b);
void init_render_cache(t_game *game);

// ========================================================================== 
//                           RAY FUNCTIONS                                    
// ========================================================================== 

/* ray_init.c */
void init_ray(t_game *game, t_ray *ray, int x);
void init_ray_distances(t_ray *ray);
void calc_step_and_side_dist(t_game *game, t_ray *ray);
void calc_step_x(t_game *game, t_ray *ray);
void calc_step_y(t_game *game, t_ray *ray);

/* ray_dda.c */
void perform_dda(t_game *game, t_ray *ray);
void dda_step(t_ray *ray);
bool check_bounds(t_game *game, t_ray *ray);
bool check_wall_hit(t_game *game, t_ray *ray);

/* ray_wall_calc.c */
void calc_wall_height(t_game *game, t_ray *ray);
void calc_perp_wall_dist(t_game *game, t_ray *ray);
void calc_line_height(t_game *game, t_ray *ray);
void calc_draw_limits(t_game *game, t_ray *ray);

/* ray_texture.c */
t_texture *select_texture(t_game *game, t_ray *ray);
t_texture *select_vertical_texture(t_ray *ray);
t_texture *select_horizontal_texture(t_ray *ray);
uint32_t get_texture_pixel(t_texture *tex, int texX, int texY);
bool is_valid_texture_coord(t_texture *tex, int texX, int texY);

/* render_column.c */
void draw_column_textured(t_game *game, t_ray *ray, int x);
void setup_column_data(t_game *game, t_ray *ray, t_column_data *data);
void calc_texture_coordinates(t_game *game, t_ray *ray, t_column_data *data);
void adjust_texture_x(t_ray *ray, t_column_data *data);
void render_ceiling(int x, t_column_data *data);
void render_wall(int x, t_column_data *data);
void render_floor(int x, t_column_data *data);

/* raycasting_main.c */
void raycasting(t_game *game);
bool validate_game_data(t_game *game);
void init_cache_if_needed(t_game *game);
void display_fps(void);
void cast_single_ray(t_game *game, t_ray *ray, int x);

#endif