# Snake Game

## Description
A terminal-based implementation of the classic Snake game, written in Python.

## Setup and Installation

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd snake-game
    ```

2.  **Create a virtual environment and install dependencies:**
    This project uses `uv` for environment management.
    ```bash
    uv init
    uv sync
    ```

## How to Run
To start the game, run the following command from the project's root directory:
```bash
uv run python snake_game.py
```

## How to Play
-   Use the **Arrow Keys** or **W/A/S/D** keys to move the snake.
-   **W** or **Up Arrow**: Move Up
-   **S** or **Down Arrow**: Move Down
-   **A** or **Left Arrow**: Move Left
-   **D** or **Right Arrow**: Move Right
-   The goal is to eat the food (`@`) that appears on the screen.
-   Each piece of food eaten increases your score by 10 points and makes the snake longer.
-   The game ends if the snake runs into the wall or into itself.
-   Press any key to play again after a game over.
-   Press `Esc` to quit the game at any time.
