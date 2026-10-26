# cub3D

**Un motor 3D de laberinto en primera persona hecho en C con raycasting, como Wolfenstein 3D.**

[English](README.md) · [Català](README.ca.md) · **Español**

`Parte del Common Core de 42 Barcelona` · `Rango 4` · `C` · `MiniLibX` · `Raycasting`

<p align="center"><img src="demo/demo.gif" alt="Demo" width="640" /></p>

---

## Descripción

`cub3D` lee un fichero de descripción de mapa (`.cub`) y muestra el laberinto en primera persona, con una textura distinta para cada orientación de pared y colores propios para el suelo y el techo. También dibuja un minimapa 2D con la posición del jugador.

## Qué enseña

- **Raycasting**: convertir una cuadrícula 2D en una imagen 3D lanzando un rayo por cada columna de la pantalla.
- El **algoritmo DDA** para encontrar qué pared toca cada rayo, rápido y sin huecos.
- Trigonometría y vectores para la dirección del jugador, la rotación y el campo de visión.
- Mapeado de texturas: elegir el píxel correcto de la textura para cada punto de la pared.
- Leer un fichero de configuración con reglas estrictas y validar el mapa con flood fill.

## Cómo funciona

Para cada columna de la ventana, sale un rayo desde el jugador en la dirección en la que mira. El algoritmo DDA avanza el rayo de casilla en casilla hasta que toca una pared. La distancia a esa pared decide lo alta que se dibuja la columna: las paredes cercanas son altas y las lejanas, bajas. El lado que ha tocado el rayo (norte, sur, este u oeste) elige la textura, y el punto exacto del impacto elige la columna de la textura. Usar la distancia perpendicular evita el efecto "ojo de pez".

| Tecla | Acción |
|:--:|:--|
| `W` `S` | avanzar y retroceder |
| `A` `D` | moverse a izquierda y derecha |
| `←` `→` | girar la cámara |
| `ESC` | salir |

Ejemplo de fichero `.cub`:

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0

111111
100001
10E001
111111
```

`NO`, `SO`, `WE`, `EA` son las texturas de las paredes, `F` y `C` los colores del suelo y el techo en RGB, `1` es pared, `0` es suelo, y `N`, `S`, `E` o `W` es la posición y dirección inicial del jugador.

## Compilar y ejecutar

```bash
git clone https://github.com/acarranz-dev/cube3D.git
cd cube3D

sudo apt install libx11-dev libxext-dev libbsd-dev   # MiniLibX dependencies
make
./cub3D maps/map.cub
```

## Estructura del proyecto

```
cube3D/
├── src/
│   ├── parser/     # reads the .cub file: textures, colours, map and flood fill validation
│   ├── init/       # window, images and player start direction
│   ├── render/     # raycasting and textured wall columns
│   ├── minimap/    # 2D minimap and player movement
│   └── utils/
├── maps/           # example .cub maps
├── textures/
├── libraries/      # libft and MiniLibX
└── Makefile
```

---

[Más proyectos en mi perfil](https://github.com/acarranz-dev)
