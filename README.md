# Snake Game

A terminal-based snake game built with C++ and PDCurses.

## How to Play

- Use the arrow keys or WASD to control the snake.
- Eat the food (*) to grow and increase your score.
- Avoid running into the walls or the snake's own body.

## Build and Run Instructions

### Prerequisites

- C++ Compiler (G++ recommended)
- CMake
- PDCurses

### Build

1.  Create a `build` directory:
    ```
    mkdir build
    cd build
    ```
2.  Run CMake to generate the build files. You will need to provide the path to your PDCurses installation.
    ```
    cmake -DPDCURSES_DIR=/path/to/pdcurses ..
    ```
3.  Compile the project:
    ```
    cmake --build .
    ```

### Run

After a successful build, the executable will be located in the `build/Debug` directory.

```
./build/Debug/snake_game
```
