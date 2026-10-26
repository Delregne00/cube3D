# cub3D

**Un motor 3D de laberint en primera persona fet en C amb raycasting, com Wolfenstein 3D.**

[English](README.md) · **Català** · [Español](README.es.md)

`Part del Common Core de 42 Barcelona` · `Rang 4` · `C` · `MiniLibX` · `Raycasting`

<p align="center"><img src="demo/demo.gif" alt="Demo" width="640" /></p>

---

## Descripció

`cub3D` llegeix un fitxer de descripció de mapa (`.cub`) i mostra el laberint en primera persona, amb una textura diferent per a cada orientació de paret i colors propis per al terra i el sostre. També dibuixa un minimapa 2D amb la posició del jugador.

## Què ensenya

- **Raycasting**: convertir una graella 2D en una imatge 3D llançant un raig per cada columna de la pantalla.
- L'**algorisme DDA** per trobar quina paret toca cada raig, ràpid i sense forats.
- Trigonometria i vectors per a la direcció del jugador, la rotació i el camp de visió.
- Mapatge de textures: triar el píxel correcte de la textura per a cada punt de la paret.
- Llegir un fitxer de configuració amb regles estrictes i validar el mapa amb flood fill.

## Com funciona

Per a cada columna de la finestra, surt un raig des del jugador en la direcció en què mira. L'algorisme DDA avança el raig de casella en casella fins que toca una paret. La distància a aquesta paret decideix com d'alta es dibuixa la columna: les parets properes són altes i les llunyanes, baixes. El costat que ha tocat el raig (nord, sud, est o oest) tria la textura, i el punt exacte de l'impacte tria la columna de la textura. Fer servir la distància perpendicular evita l'efecte "ull de peix".

| Tecla | Acció |
|:--:|:--|
| `W` `S` | avançar i retrocedir |
| `A` `D` | moure's a esquerra i dreta |
| `←` `→` | girar la càmera |
| `ESC` | sortir |

Exemple de fitxer `.cub`:

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

`NO`, `SO`, `WE`, `EA` són les textures de les parets, `F` i `C` els colors del terra i el sostre en RGB, `1` és paret, `0` és terra, i `N`, `S`, `E` o `W` és la posició i direcció inicial del jugador.

## Compilar i executar

```bash
git clone https://github.com/acarranz-dev/cube3D.git
cd cube3D

sudo apt install libx11-dev libxext-dev libbsd-dev   # MiniLibX dependencies
make
./cub3D maps/map.cub
```

## Estructura del projecte

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

[Més projectes al meu perfil](https://github.com/acarranz-dev)
