<div align="center">

# cube3D

**A 3D first-person perspective raycaster developed in C as part of the 42 School curriculum**

*Inspired by the world-famous Wolfenstein 3D game - the first FPS in gaming history*

---

</div>

## Demo
<div align="center">

![cube3D gameplay](demo/demo.gif)

*Navigate through a 3D maze using raycasting rendering techniques*

</div>

---

## Objective

Create a dynamic 3D view inside a maze using raycasting principles. The project implements a first-person perspective game where players navigate through a textured 3D environment, demonstrating fundamental computer graphics concepts and mathematical applications in game development.

---

## Controls

<div align="center">

| Key | Action | Key | Action |
|:---:|:------:|:---:|:------:|
| **W** | Move Forward | **S** | Move Backward |
| **A** | Move Left | **D** | Move Right |
| **←** | Rotate Left | **→** | Rotate Right |
| **↑** | Move Forward | **↓** | Move Backward |
| **ESC** | Exit Game | **Q** | Exit Game |

</div>

### Bonus Controls (if implemented)
| Key | Action | Mouse | Action |
|:---:|:------:|:-----:|:------:|
| **Mouse Move** | Look Around | **Mouse Click** | Interact |

---

## Installation

<details>
<summary><b>Prerequisites</b></summary>

- **MiniLibX** graphics library
- **Make** build system
- **GCC** compiler
- **X11 development libraries** (Linux)
- **Math library** (libm)

</details>

### MiniLibX Installation

#### macOS
```bash
# MiniLibX is usually included with 42 environment
# Or install via:
brew install minilibx
```

#### Linux
```bash
# Install required dependencies
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Clone MiniLibX
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
```

### Build & Run

```bash
# Clone the repository
git clone https://github.com/Delregne00/cube3D.git
cd cube3D

# Compile the project
make

# Run the game with a map file
./cub3D maps/map.cub
```

### Bonus Version
```bash
# Compile bonus version (with additional features)
make bonus

# Run bonus version
./cub3D_bonus maps/map.cub
```

---

## Map Configuration

Maps use the `.cub` extension and contain scene description information:

### Configuration File Structure

```
R 1920 1080									   # Resolution (width height)
NO ./textures/north_wall.xpm				   # North wall texture
SO ./textures/south_wall.xpm				   # South wall texture
WE ./textures/west_wall.xpm					   # West wall texture
EA ./textures/east_wall.xpm					   # East wall texture
S  ./textures/sprite.xpm					   # Sprite texture (bonus)
F  220,100,0								   # Floor color (R,G,B)
C  225,200,200								   # Ceiling color (R,G,B)

		1111111111111111111111111
		1000000000110000000000001
		1011000001110000002000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10002000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements

<div align="center">

| Symbol | Element | Description |
|:------:|:-------:|:-----------:|
| `0` | Empty space | Walkable floor areas |
| `1` | Wall | Solid barriers with textures |
| `N` | Player North | Starting position facing North |
| `S` | Player South | Starting position facing South |
| `E` | Player East | Starting position facing East |
| `W` | Player West | Starting position facing West |
| `2` | Sprite | Interactive objects (bonus) |

</div>

### Map Requirements

<table>
<tr>
<td width="50%">

**Structure Rules:**
- Must be surrounded by walls (`1`)
- Exactly one player starting position
- Valid `.xpm` texture files required
- Floor and ceiling colors in RGB format
- Resolution within system limits

</td>
<td width="50%">

**Validation Rules:**
- Map must be closed (no holes in walls)
- All textures must be accessible
- Player must be placed on empty space (`0`)
- Invalid characters are rejected
- File extension must be `.cub`

</td>
</tr>
</table>

---

## Technical Implementation

The project implements a **sophisticated raycasting engine** based on mathematical principles used in classic FPS games.

<details>
<summary><b>Raycasting Algorithm</b></summary>

### **Core Concept**
Raycasting is a rendering technique to create a 3D perspective in a 2D map. The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture).

### **Implementation Steps**
1. **Ray Generation**: Cast rays from player position for each screen column
2. **Wall Detection**: Use DDA algorithm to find wall intersections
3. **Distance Calculation**: Compute perpendicular distance to avoid fisheye effect
4. **Wall Projection**: Calculate wall height based on distance
5. **Texture Mapping**: Apply appropriate texture based on wall direction

### **Mathematical Foundation**
- **Field of View**: Typically 60 degrees for realistic perspective
- **Triangle Similarity**: Used for wall height projection
- **Vector Mathematics**: Player direction and movement calculations
- **DDA Algorithm**: Efficient ray-grid intersection detection

</details>

<details>
<summary><b>Rendering Pipeline</b></summary>

### **Frame Rendering Process**
1. **Clear Frame Buffer**: Prepare canvas for new frame
2. **Cast Rays**: For each screen column (typically 640-1920 rays)
3. **Wall Rendering**: Draw textured wall segments
4. **Floor/Ceiling Fill**: Apply colors to upper and lower sections
5. **Sprite Rendering**: Draw objects in correct depth order (bonus)
6. **Frame Display**: Present completed frame to screen

### **Performance Optimizations**
- **Column-based Rendering**: Only vertical strips, not individual pixels
- **Integer DDA**: Fast grid traversal algorithm
- **Texture Caching**: Efficient memory management
- **Fisheye Correction**: Mathematical distortion compensation

</details>

<details>
<summary><b>Input System</b></summary>

### **Movement Mechanics**
- **Forward/Backward**: Move along current facing direction
- **Strafing**: Side-to-side movement perpendicular to view direction
- **Rotation**: Adjust view angle (keyboard or mouse)
- **Collision Detection**: Prevent movement through walls

### **Event Processing**
- **Real-time Input**: Responsive keyboard/mouse handling
- **Smooth Movement**: Frame-rate independent motion
- **State Management**: Track player position and orientation

</details>

---

## Performance & Quality

### Performance Optimizations
- **Efficient Raycasting**: Optimized DDA algorithm for fast wall detection
- **Texture Management**: Smart caching and memory usage
- **Frame Rate Control**: Consistent 60fps targeting
- **Mathematical Precision**: Double-precision calculations where needed

### Quality Assurance
The project includes comprehensive validation:
- Map format and structure verification
- Texture file accessibility checking
- Memory leak prevention and detection
- Error handling for invalid configurations
- Cross-platform compatibility testing

---

## Documentation

For detailed technical documentation about the implementation:

**[Complete Technical Wiki](https://app.devin.ai/wiki/Delregne00/cube3D)**

<details>
<summary><b>The wiki covers:</b></summary>

- Raycasting algorithm implementation details
- Mathematical foundations and formulas
- MiniLibX graphics library usage
- Texture mapping and rendering techniques
- Performance optimization strategies
- Debugging and testing methodologies

</details>

---

## Built With

<table>
<tr>
<td width="50%">

**Core Technologies:**
- **Language**: C (C99 standard)
- **Graphics**: MiniLibX library
- **Build System**: Custom Makefile with automated dependency management
- **Math Library**: Standard C math library (libm)

</td>
<td width="50%">

**Custom Libraries:**
- **libft**: Custom utility library
- **ft_printf**: Custom formatting system
- **get_next_line**: File reading utility

</td>
</tr>
</table>

---

## Development Environment

### Project Structure
```
cube3D/
├── src/					# Core raycasting engine
│	├── parsing/		   # Map and config file parsing
│	├── raycasting/		   # Core rendering algorithms
│	├── graphics/		   # MiniLibX interface
│	└── utils/			   # Utility functions
├── includes/			   # Header files and definitions
├── maps/				   # Game level files (.cub format)
├── textures/			   # Wall and sprite textures (.xpm)
├── libft/				   # Custom utility library
├── demo/				   # Gameplay videos and screenshots
└── Makefile			  # Build configuration
```

### Build Targets
```bash
make		  # Build the mandatory executable
make bonus	  # Build bonus version with additional features
make clean	  # Remove object files
make fclean   # Full clean (remove all generated files)
make re		  # Rebuild everything from scratch
```

---

## Key Features

<div align="center">

**Real-time Raycasting** • **Textured Walls** • **Player Movement** • **Collision Detection** • **Map Parsing** • **Memory Management**

</div>

<table>
<tr>
<td width="50%">

**Mandatory Features:**
- First-person 3D view using raycasting
- Textured walls with different textures per direction
- Smooth player movement and rotation
- Map parsing from configuration files
- Floor and ceiling color rendering

</td>
<td width="50%">

**Bonus Features (if implemented):**
- Wall collision detection
- Minimap display
- Mouse-controlled camera rotation
- Sprite rendering and interaction
- Enhanced visual effects

</td>
</tr>
</table>

---

## 42 School Requirements

This project fulfills **all requirements** for the **cube3D** project at 42 School:

<div align="center">

| Requirement | Status |
|:------------|:------:|
| Use MiniLibX for graphics | ✅ |
| Implement raycasting algorithm | ✅ |
| Parse map configuration files | ✅ |
| Handle different wall textures | ✅ |
| Smooth player movement (WASD) | ✅ |
| Camera rotation with arrow keys | ✅ |
| Window management (close, ESC) | ✅ |
| Floor and ceiling colors | ✅ |
| Error handling and validation | ✅ |
| No memory leaks | ✅ |

</div>

---

<div align="center">

**Developed by [Delregne00] as part of the 42 School curriculum**

</div>
