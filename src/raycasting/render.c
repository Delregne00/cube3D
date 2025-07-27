#include "includes/cube.h"

static void put_pixel(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return;

	uint32_t *pixels = (uint32_t *)game->addr;
	pixels[y * WIN_W + x] = color;
}


void render(void *param)
{
	t_game *game = (t_game *)param;

	// Netegem la imatge (exemple: color fosc)
	memset(game->addr, 0, WIN_W * WIN_H * sizeof(uint32_t));

	// Exemples de píxels:
	for (int x = 0; x < WIN_W; x++)
		for (int y = 0; y < WIN_H / 2; y++)
			put_pixel(game, x, y, 0xFF87CEEB); // blau cel

	for (int x = 0; x < WIN_W; x++)
		for (int y = WIN_H / 2; y < WIN_H; y++)
			put_pixel(game, x, y, 0xFF228B22); // verd gespa

	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
