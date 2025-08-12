#include "MLX42/MLX42.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

/* primer compilar mlx y libft despres fer servir la comanda  directe a terminal:
gcc -o raycasting raycasting.c \
    -Iincludes \
    -Ilibraries/MLX42/include \
    -Llibraries/libft -lft \
    -Llibraries/MLX42/build -lmlx42 \
    -lglfw -lGL -lm
*/

// ==================== CONFIGURACIÓN ====================
#define CELL_SIZE       40           // Tamaño de cada celda del mapa
#define MAP_WIDTH       10           // Ancho del mapa
#define MAP_HEIGHT      8            // Alto del mapa
#define WINDOW_WIDTH    (MAP_WIDTH * CELL_SIZE)
#define WINDOW_HEIGHT   (MAP_HEIGHT * CELL_SIZE)
#define TITLE           "Raycasting 2D - Vista Top-Down"

// ==================== CONFIGURACIÓN DE RAYCASTING ====================
#define FOV             90.0f        // Campo de visión en grados
#define NUM_RAYS        120           // Número de rayos
#define RAY_LENGTH      150.0f        // Longitud máxima del rayo
#define RAY_STEP        0.02f        // Paso del rayo (precisión)

// ==================== CONFIGURACIÓN DE MOVIMIENTO ====================
#define MOVE_SPEED      0.02f        // Velocidad de movimiento
#define ROT_SPEED       0.02f        // Velocidad de rotación
#define MOUSE_SENS      0.01f        // Sensibilidad del ratón

// ==================== COLORES ====================
#define COLOR_WALL      0x333333FF   // Paredes - gris oscuro
#define COLOR_FLOOR     0xEEEEEEFF   // Suelo - gris claro
#define COLOR_PLAYER    0xFF0000FF   // Jugador - rojo
#define COLOR_RAY       0x00FF00FF   // Rayos - verde
#define COLOR_RAY_HIT   0xFFFF00FF   // Punto de impacto - amarillo
#define COLOR_GRID      0x888888FF   // Grid - gris medio
#define COLOR_BLACK     0x000000FF   // Negro
#define COLOR_DIR       0xFF6600FF   // Dirección del jugador - naranja

// ==================== ESTRUCTURAS ====================

// Estructura del jugador
typedef struct s_player
{
    float x;                         // Posición X (en celdas)
    float y;                         // Posición Y (en celdas)
    float angle;                     // Ángulo de visión (radianes)
    float dx;                        // Componente X de dirección
    float dy;                        // Componente Y de dirección
} t_player;

// Estructura de un rayo
typedef struct s_ray
{
    float angle;                     // Ángulo del rayo
    float length;                    // Longitud del rayo
    float hit_x;                     // Punto de impacto X
    float hit_y;                     // Punto de impacto Y
    bool hit_wall;                   // Si golpeó una pared
} t_ray;

// ==================== VARIABLES GLOBALES ====================
mlx_t* mlx;
mlx_image_t* img;
t_player player;
bool keys[512];                      // Estado de las teclas
int mouse_x, mouse_y;
bool first_mouse = true;

// Mapa del mundo
char world_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "1111111111",
    "1000000001",
    "1011001001",
    "1000000001",
    "1001110001",
    "1000P00001",
    "1000001001",
    "1111111111"
};

// ==================== FUNCIONES BÁSICAS DE DIBUJO ====================

void draw_pixel(int x, int y, uint32_t color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        mlx_put_pixel(img, x, y, color);
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            draw_pixel(x + j, y + i, color);
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int x = x1, y = y1;
    
    while (1)
    {
        draw_pixel(x, y, color);
        
        if (x == x2 && y == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
}

void clear_screen(uint32_t color)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            draw_pixel(x, y, color);
        }
    }
}

// ==================== FUNCIONES DEL JUGADOR ====================

void init_player(void)
{
    // Buscar posición inicial del jugador en el mapa
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            if (world_map[row][col] == 'P')
            {
                player.x = col + 0.5f;  // Centro de la celda
                player.y = row + 0.5f;
                player.angle = 0.0f;    // Mirando hacia la derecha
                player.dx = cos(player.angle);
                player.dy = sin(player.angle);
                
                // Limpiar la marca del mapa
                world_map[row][col] = '0';
                
                printf("🎮 Jugador inicializado en (%.2f, %.2f)\n", player.x, player.y);
                return;
            }
        }
    }
    
    // Si no se encuentra 'P', usar posición por defecto
    player.x = 1.5f;
    player.y = 1.5f;
    player.angle = 0.0f;
    player.dx = 1.0f;
    player.dy = 0.0f;
}

bool is_valid_position(float x, float y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    // Verificar límites
    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        return false;
    
    // Verificar si es una pared
    return (world_map[map_y][map_x] != '1');
}

void update_player(void)
{
    float new_x = player.x;
    float new_y = player.y;
    
    // Movimiento hacia adelante/atrás
    if (keys[MLX_KEY_W])
    {
        new_x += player.dx * MOVE_SPEED;
        new_y += player.dy * MOVE_SPEED;
    }
    if (keys[MLX_KEY_S])
    {
        new_x -= player.dx * MOVE_SPEED;
        new_y -= player.dy * MOVE_SPEED;
    }
    
    // Movimiento lateral (strafe)
    if (keys[MLX_KEY_A])
    {
        new_x += player.dy * MOVE_SPEED;  // Perpendicular
        new_y -= player.dx * MOVE_SPEED;
    }
    if (keys[MLX_KEY_D])
    {
        new_x -= player.dy * MOVE_SPEED;
        new_y += player.dx * MOVE_SPEED;
    }
    
    // Verificar colisiones antes de mover
    if (is_valid_position(new_x, player.y))
        player.x = new_x;
    if (is_valid_position(player.x, new_y))
        player.y = new_y;
    
    // Rotación con teclas
    if (keys[MLX_KEY_LEFT])
        player.angle -= ROT_SPEED;
    if (keys[MLX_KEY_RIGHT])
        player.angle += ROT_SPEED;
    
    // Normalizar ángulo
    while (player.angle < 0) player.angle += 2 * M_PI;
    while (player.angle >= 2 * M_PI) player.angle -= 2 * M_PI;
    
    // Actualizar componentes de dirección
    player.dx = cos(player.angle);
    player.dy = sin(player.angle);
}

// ==================== SISTEMA DE RAYCASTING ====================

t_ray cast_ray(float start_x, float start_y, float angle)
{
    t_ray ray;
    float ray_x = start_x;
    float ray_y = start_y;
    float ray_dx = cos(angle);
    float ray_dy = sin(angle);
    
    ray.angle = angle;
    ray.length = 0.0f;
    ray.hit_wall = false;
    
    // Marcha del rayo
    while (ray.length < RAY_LENGTH)
    {
        ray_x += ray_dx * RAY_STEP;
        ray_y += ray_dy * RAY_STEP;
        ray.length += RAY_STEP;
        
        // Verificar colisión
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        
        // Verificar límites
        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        {
            ray.hit_wall = true;
            break;
        }
        
        // Verificar pared
        if (world_map[map_y][map_x] == '1')
        {
            ray.hit_wall = true;
            break;
        }
    }
    
    ray.hit_x = ray_x;
    ray.hit_y = ray_y;
    
    return ray;
}

// ==================== FUNCIONES DE RENDERIZADO ====================

void draw_map(void)
{
    // Dibujar celdas del mapa
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;
            uint32_t color;
            
            if (world_map[row][col] == '1')
                color = COLOR_WALL;
            else
                color = COLOR_FLOOR;
            
            draw_rectangle(x, y, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void draw_grid(void)
{
    // Líneas verticales
    for (int x = 0; x <= MAP_WIDTH; x++)
    {
        int pixel_x = x * CELL_SIZE;
        draw_line(pixel_x, 0, pixel_x, WINDOW_HEIGHT - 1, COLOR_GRID);
    }
    
    // Líneas horizontales
    for (int y = 0; y <= MAP_HEIGHT; y++)
    {
        int pixel_y = y * CELL_SIZE;
        draw_line(0, pixel_y, WINDOW_WIDTH - 1, pixel_y, COLOR_GRID);
    }
}

void draw_player(void)
{
    int center_x = (int)(player.x * CELL_SIZE);
    int center_y = (int)(player.y * CELL_SIZE);
    int size = 8;
    
    // Dibujar cuerpo del jugador
    draw_rectangle(center_x - size/2, center_y - size/2, size, size, COLOR_PLAYER);
    
    // Dibujar indicador de dirección
    int dir_x = center_x + (int)(player.dx * size * 2);
    int dir_y = center_y + (int)(player.dy * size * 2);
    draw_line(center_x, center_y, dir_x, dir_y, COLOR_DIR);
}

void draw_rays(void)
{
    float start_angle = player.angle - (FOV * M_PI / 180.0f) / 2.0f;
    float angle_step = (FOV * M_PI / 180.0f) / NUM_RAYS;
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float ray_angle = start_angle + i * angle_step;
        t_ray ray = cast_ray(player.x, player.y, ray_angle);
        
        // Coordenadas en píxeles
        int start_x = (int)(player.x * CELL_SIZE);
        int start_y = (int)(player.y * CELL_SIZE);
        int end_x = (int)(ray.hit_x * CELL_SIZE);
        int end_y = (int)(ray.hit_y * CELL_SIZE);
        
        // Dibujar rayo
        draw_line(start_x, start_y, end_x, end_y, COLOR_RAY);
        
        // Dibujar punto de impacto si golpeó una pared
        if (ray.hit_wall)
        {
            draw_rectangle(end_x - 1, end_y - 1, 3, 3, COLOR_RAY_HIT);
        }
    }
}

void render_scene(void)
{
    // 1. Limpiar pantalla
    clear_screen(COLOR_BLACK);
    
    // 2. Dibujar mapa
    draw_map();
    
    // 3. Dibujar grid
    draw_grid();
    
    // 4. Dibujar rayos
    draw_rays();
    
    // 5. Dibujar jugador
    draw_player();
}

// ==================== MANEJO DE EVENTOS ====================

void handle_key(mlx_key_data_t keydata, void* param)
{
    (void)param;
    
    // Actualizar estado de teclas
    if (keydata.action == MLX_PRESS)
        keys[keydata.key] = true;
    else if (keydata.action == MLX_RELEASE)
        keys[keydata.key] = false;
    
    // Comandos especiales
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
        {
            printf("👋 Saliendo...\n");
            mlx_close_window(mlx);
        }
        else if (keydata.key == MLX_KEY_R)
        {
            printf("🔄 Reiniciando jugador...\n");
            init_player();
        }
    }
}

void handle_mouse_move(double xpos, double ypos, void* param)
{
    (void)param;
    
    if (first_mouse)
    {
        mouse_x = (int)xpos;
        mouse_y = (int)ypos;
        first_mouse = false;
        return;
    }
    
    int xoffset = (int)xpos - mouse_x;
    mouse_x = (int)xpos;
    mouse_y = (int)ypos;
    
    // Aplicar rotación con el ratón
    player.angle += xoffset * MOUSE_SENS;
    
    // Normalizar ángulo
    while (player.angle < 0) player.angle += 2 * M_PI;
    while (player.angle >= 2 * M_PI) player.angle -= 2 * M_PI;
    
    // Actualizar componentes de dirección
    player.dx = cos(player.angle);
    player.dy = sin(player.angle);
}

void game_loop(void* param)
{
    (void)param;
    
    // Actualizar jugador
    update_player();
    
    // Renderizar escena
    render_scene();
}

// ==================== FUNCIÓN PRINCIPAL ====================

int main(void)
{
    printf("🚀 RAYCASTING 2D - Vista Top-Down\n");
    printf("==================================\n\n");
    
    // Inicializar MLX
    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, true);
    if (!mlx)
    {
        printf("❌ Error: No se pudo inicializar MLX\n");
        return (1);
    }
    
    // Crear imagen
    img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
    {
        printf("❌ Error: No se pudo crear la imagen\n");
        mlx_terminate(mlx);
        return (1);
    }
    
    // Mostrar imagen
    if (mlx_image_to_window(mlx, img, 0, 0) == -1)
    {
        printf("❌ Error: No se pudo mostrar la imagen\n");
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return (1);
    }
    
    // Inicializar estado del juego
    init_player();
    
    // Inicializar array de teclas
    for (int i = 0; i < 512; i++)
        keys[i] = false;
    
    // Configurar eventos
    mlx_key_hook(mlx, handle_key, NULL);
    mlx_cursor_hook(mlx, handle_mouse_move, NULL);
    mlx_loop_hook(mlx, game_loop, NULL);
    
    // Mostrar controles
    printf("📋 CONTROLES:\n");
    printf("  WASD         - Movimiento (W/S = adelante/atrás, A/D = lateral)\n");
    printf("  Flechas      - Rotación manual\n");
    printf("  Ratón        - Rotación libre\n");
    printf("  R            - Reiniciar posición\n");
    printf("  ESC          - Salir\n");
    printf("\n✨ Configuración:\n");
    printf("  Ventana: %dx%d píxeles\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("  Mapa: %dx%d celdas\n", MAP_WIDTH, MAP_HEIGHT);
    printf("  FOV: %.0f grados\n", FOV);
    printf("  Rayos: %d\n", NUM_RAYS);
    printf("  Alcance: %.1f celdas\n\n", RAY_LENGTH);
    
    // Iniciar bucle principal
    mlx_loop(mlx);
    
    // Limpiar
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    printf("👋 ¡Programa terminado!\n");
    
    return (0);
}

/*
 * ==================== SISTEMA COMPLETO DE RAYCASTING 2D ====================
 * 
 * 🎯 CARACTERÍSTICAS IMPLEMENTADAS:
 * 
 * ✅ Sistema de mapas 2D con paredes y suelo
 * ✅ Jugador con posición y orientación
 * ✅ Movimiento fluido (WASD + rotación)
 * ✅ Control con ratón para rotación libre
 * ✅ Sistema de raycasting con múltiples rayos
 * ✅ Campo de visión configurable
 * ✅ Detección de colisiones precisa
 * ✅ Renderizado en tiempo real
 * ✅ Grid visual para debugging
 * ✅ Indicadores visuales (jugador, rayos, impactos)
 * 
 * 🔧 PARÁMETROS CONFIGURABLES:
 * 
 * - CELL_SIZE: Tamaño de cada celda del mapa
 * - MAP_WIDTH/HEIGHT: Dimensiones del mapa
 * - FOV: Campo de visión en grados
 * - NUM_RAYS: Cantidad de rayos para casting
 * - RAY_LENGTH: Alcance máximo de los rayos
 * - MOVE_SPEED/ROT_SPEED: Velocidades de movimiento
 * - MOUSE_SENS: Sensibilidad del ratón
 * 
 * 🚀 PRÓXIMO PASO PARA 3D:
 * 
 * Para convertir a 3D necesitarás:
 * 1. Usar las distancias de los rayos para calcular altura de paredes
 * 2. Crear una segunda ventana/vista para el renderizado 3D
 * 3. Implementar proyección perspectiva
 * 4. Añadir texturas y shading
 * 
 * ¡ESTE ES TU MOTOR DE RAYCASTING BASE COMPLETO! 🎉
 */