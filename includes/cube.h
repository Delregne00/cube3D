/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cube.h  											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: acarranz <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/01 17:08:56 by acarranz		   #+#	  #+#			  */
/*	 Updated: 2025/07/01 17:08:56 by acarranz		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

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
# include "libraries/minilibx/mlx.h"

//Macros
# define MAX_MAP_SIZE	100
# define WIN_W			1920
# define WIN_H			1080
# define TEX_NO			0
# define TEX_SO			1
# define TEX_WE			2
# define TEX_EA			3

// Macros per al minimap
# define MINIMAP_SCALE		5	// Mida de cada cella del mapa
# define MINIMAP_OFFSET_X	20	// Posició X del minimap en la finestra
# define MINIMAP_OFFSET_Y	20	// Posició Y del minimap en la finestra
# define PLAYER_SIZE		3	// Mida del punt del jugador
# define PLAYER_DIR_LENGTH	15	// Longitut de la línia de direcció

// Colors minimap
# define COLOR_WALL		0xFF0000
# define COLOR_FLOOR	0xFFFFFF
# define COLOR_PLAYER	0x00FF00
# define COLOR_DIR		0x0000FF
# define COLOR_BLACK	0x000000

// Macros tecles minilibX
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

// Macros velocitat player
# define MOVE_SPEED	0.15	//0.01: Molt lenta, 0.20: Molt ràpida
# define ROT_SPEED	0.10

# define NORTH		"NO "
# define SOUTH 		"SO "
# define WEST 		"WE "
# define EAST		"EA "
# define FLOOR		"F "
# define CEILING	"C "

/* ======================================================================== */
/*							STRUCTURES										*/
/* ======================================================================== */

// Variables globals x estat de tecles
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct s_line_params
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line_params;

typedef struct s_square_params
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square_params;

typedef struct s_line_data
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_line_data;

typedef struct s_map
{
	char	**map;
	int		filas;
	int		max_columnas;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_data
{
	char	**textures;		// [0]=NO, [1]=SO, [2]=WE, [3]=EA
	int		f_color[3];		// Floor RGB
	int		c_color[3];		// Ceiling RGB
}	t_data;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	void	*img;		// punter a la imatge MLX
	char	*addr;		// punter a la memòria de píxels
	int		width;		// amplada en píxels
	int		height;		// alçada en píxels
	int		bpp;		// bits per píxel
	int		line_len;	// bytes per línia
	int		endian;		// endianess (normalment 0)
}	t_texture;

typedef struct s_elemnts{
	int	north;
	int	south;
	int	west;
	int	east;
	int	floor;
	int	ceiling;

}	t_elements;

typedef struct s_cube
{
	t_data		*data;
	t_map		*map;
	t_elements	*elements;
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_west;
	t_texture	tex_east;
}	t_cube;


typedef struct s_render_cache
{
	uint32_t	floor_color;
	uint32_t	ceil_color;
	double		sin_rot;
	double		cos_rot;
	t_texture	*tex_cache[4];	// Cache de textures
	int			initialized;
}	t_render_cache;

typedef struct s_game
{
	t_cube			*cube;
	t_player		player;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	t_render_cache  cache;
}	t_game;

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
	t_game		*game;
	t_collector	**collector;
}	t_game_loop_param;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_column_data
{
	t_texture	*tex;
	uint32_t	*pixels;
	int			width;
	int			height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		step;
	double		tex_pos;
}	t_column_data;

/* ======================================================================== */
/*						UTILITY FUNCTIONS									*/
/* ======================================================================== */

/* util/utils.c */
void		freer(void **ptr);
void		print_msg(const char *msg);
void		exit_program(t_collector **collector, const char *msg,
				bool should_exit, void *mlx);

/* ======================================================================== */
/*						MEMORY MANAGEMENT									*/
/* ======================================================================== */

/* util/collector.c */
void		collector_remove_ptr(t_collector **collector, void *ptr);
void		collector_cleanup(t_collector **collector, void *mlx);
void		collector_append(t_collector **collector, void *ptr,
				t_resource_type type, void *mlx);

/* ======================================================================== */
/*						INIT FUNCTIONS										*/
/* ======================================================================== */
/* init/cube_init.c */
t_cube		*cube_init(t_collector **collector);
void		cube_free(t_cube *cube);

/* init/game_init.c */
t_game		*game_init(t_cube *cube, t_collector **collector);

/* init/game_funcs.c */
void		player_init(t_game *game);
int			window_close(t_game_loop_param *p);
int			game_loop(void *param);
void		hooks_setup(t_game_loop_param *p);

/* init/player_direction.c */
void		player_set_direction(t_player *player, char direction);

/* ======================================================================== */
/*						PARSER FUNCTIONS									*/
/* ======================================================================== */
/* PARSER FUNCTIONS */
bool		parser(t_cube *cube, char *file, t_collector **collector);
bool		validation_file(t_cube *cube, char *file, t_collector **collector);
bool		process_rgb_lines(t_cube *cube, char *line, int i);
bool		process_texture_lines(t_cube *cube, char *line, int i, t_collector **collector);
// bool		parse_line(t_cube *cube, char *line, char *expected, int len);
bool		process_rgb(t_cube *cube, char *line, int i);
void		map_to_struct(t_cube *cube, char **map, t_collector **collector);
bool        validate_map(t_map *map);
bool        validate_perimisons_exist(char *file);

/* parser/parser_textures_process.c*/
bool		process_textures(t_cube *cube, char *line, int i,
				t_collector **collector);

/* Flood fill functions */
bool		is_valid_char(char c);
bool		is_transitable(char c);
bool		valid_position(t_map *map, int x, int y);
bool		**init_visited_matrix(t_map *map);
void		free_visited_matrix(bool **visited, int filas);
bool		start_position(t_map *map, int *start_x, int *start_y);
bool		start_flood_fill(t_map *map, int x, int y, bool **visited);
bool		check_connectivity(t_map *map, bool **visited);
bool		check_adjacent_positions(t_map *map, int x, int y);
bool		validate_char_and_border(t_map *map, int x, int y);
bool		flood_fill_recursive(t_map *map, int x, int y, bool **visited);
bool		initialize_flood_fill(t_map *map, bool ***visited);
bool		execute_flood_fill(t_map *map, bool **visited);
bool        flood_fill(t_map *map);
bool	check_map_closure(t_map *map, int x, int y);
bool	is_position_out_of_bounds(t_map *map, int x, int y);
void	map_dimensions(t_map *map);


/* parser/parser_utils.c */
void		assign_floor_color(t_cube *cube, char **rgb_parts);
void		assign_ceiling_color(t_cube *cube, char **rgb_parts);
void		free_rgb_parts(char **rgb_parts);
bool		validate_map_characters(char **map);
void		print_error(int n, ...);
void		free_map(t_map *map);
char		**allocate_map(void);
void		free_map_partial(char **map, int size);
char		*trim_whitespace(char *str);
void		process_empty_line(char *line);

/* ======================================================================== */
/*							MINIMAP FUNCTIONS								*/
/* ======================================================================== */
/* minimap.c */
void		minimap_render(t_game *game);
void		player_draw(t_game *game);
void		player_draw_direction(t_game *game);

/* minimap_line_draw.c */
void		line_draw(t_game *game, t_line_data *line_data);

/* minimap_draw_map.c */
void		map_grid_draw(t_game *game);

/* minimap_funcs.c */
void		square_draw(t_game *game, int x, int y,
				t_square_params *square_data);
void		put_pixel_to_image(t_game *game, int x, int y, int color);

/* ======================================================================== */
/*					PLAYER MOVEMENT FUNCTIONS								*/
/* ======================================================================== */

/* minimap/player_movement.c */
void		player_move(t_game *game, int direction);
void		player_strafe(t_game *game, int direction);
void		player_rotate(t_game *game, int direction);

/* minimap/player_movement_keys.c */
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		handle_input(t_game_loop_param *p);

/* ======================================================================== */
/*						RENDER FUNCTIONS									*/
/* ======================================================================== */

/* render/textures.c */
int			textures_load(t_game *game, t_collector **collector);

/* render/render_cache.c */
void		cache_init(t_game *game);

/* render/render_calc_step.c*/
void		calc_step_and_side_dist(t_game *game, t_ray *ray);

/* ======================================================================== */
/*						RAY FUNCTIONS										*/
/* ======================================================================== */

/* render/raycasting.c */
void		raycasting(t_game *game);

/* render/ray_init.c */
void		ray_init(t_game *game, t_ray *ray, int x);

/* render/ray_dda.c */
void		dda_perform(t_game *game, t_ray *ray);

/* render/ray_wall_calc.c */
void		wall_height_calc(t_game *game, t_ray *ray);

/* render/ray_texture.c */
t_texture	*texture_select(t_game *game, t_ray *ray);
uint32_t	texture_pixel_get(t_texture *tex, int tex_x, int tex_y);

/* render/render_column.c */
void		column_textured_draw(t_game *game, t_ray *ray, int x);

/* render/render_columns_setup.c */
void		column_data_setup(t_game *game, t_ray *ray, t_column_data *data);

#endif
