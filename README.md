# 42-cube3d

Cub3D is a ray-casting project inspired by the legendary FPS game Wolfenstein 3D. Developed using C and MLX42, this project aims to create a dynamic 3D maze exploration game from a first-person perspective. It enhances your skills in C programming, graphic design, and algorithm implementation.

## Features
- **3D Graphics**: Render a realistic 3D view of a maze using ray-casting principles.
- **Texture Mapping**: Display different wall textures based on their orientation (North, South, East, West).
- **Smooth Window Management**: Handle window operations like minimizing and switching between windows seamlessly.
- **User Controls**: Navigate the maze using W, A, S, D keys and rotate the view with arrow keys.
- **Map Parsing**: Read and parse a map file in `.cub` format.

## Requirements
- **MLX42**: Make sure to have MLX42 library installed and properly linked.
- **C Compiler**: Ensure you have GCC or Clang installed.
- **Make**: Use the `make` tool to build the project.

## Installation

1. **Clone the repository**
    ```sh
    git clone https://github.com/nima-nourinejad/42-cube3D.git
    cd 42-cube3D
    ```

2. **Install MLX42**
    Follow the instructions on the [MLX42 repository](https://github.com/codam-coding-college/MLX42) to install MLX42.

3. **Build the project**
    ```sh
    make
    ```

## Usage
1. **Run the program**
    ```sh
    ./cub3D map.cub
    ```

2. **Controls**
    - `W`: Move forward
    - `A`: Move left
    - `S`: Move backward
    - `D`: Move right
    - `Left Arrow`: Look left
    - `Right Arrow`: Look right
    - `ESC`: Exit the program

## Map File Format
The map file should be in `.cub` format and follow these rules:
- Use `0` for empty space and `1` for walls.
- Use `N`, `S`, `E`, `W` for player start positions and orientation.
- The map must be surrounded by walls.
- Example map file:
    ```
    NO ./path_to_the_north_texture
    SO ./path_to_the_south_texture
    WE ./path_to_the_west_texture
    EA ./path_to_the_east_texture
    F 220,100,0
    C 225,30,0
    
    111111
    100101
    101001
    1100N1
    111111
    ```

## Contributing
Feel free to submit issues and pull requests if you find any bugs or have suggestions for improvements.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

