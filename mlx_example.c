// cc mlx_example.c -Llibraries/minilibx -lmlx -lXext -lX11 -lm -o mlx_example
// ./mlx_example



# include "libraries/minilibx/mlx.h"
#include <stdlib.h>

#define WIN_W 800
#define WIN_H 600
#define ESC_KEY 65307   // codi per ESC en X11 (Linux)

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    int     img_w;
    int     img_h;
}   t_game;

int handle_key(int keycode, t_game *game)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return (0);
}

int main(void)
{
    t_game game;

    // Inicialitzar connexió amb el servidor X
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);

    // Crear finestra
    game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "MiniLibX Example");
    if (!game.win)
        return (1);

    // Carregar imatge XPM (ha d’existir textures/wall.xpm)
    game.img = mlx_xpm_file_to_image(game.mlx, "textures/wall_hard.xpm",
                                     &game.img_w, &game.img_h);
    if (!game.img)
        return (1);

    // Mostrar imatge a la finestra (posició 0,0)
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);

    // Hook per teclat
    mlx_key_hook(game.win, handle_key, &game);

    // Entrar al bucle d’events
    mlx_loop(game.mlx);

    return (0);
}
