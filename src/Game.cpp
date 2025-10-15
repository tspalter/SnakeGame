#include "Game.h"
#include <curses.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

Game::Game() : food(board.getWidth(), board.getHeight()), game_over(false), score(0), level(1) {
    // Initialize PDCurses
    initscr();
    // Disable echoing of characters typed by the user
    noecho();
    // Make the cursor invisible
    curs_set(0);
    // Enable special keys (like arrow keys)
    keypad(stdscr, TRUE);
    // Don't wait for input
    nodelay(stdscr, TRUE);

    // Load high score
    std::ifstream high_score_file("highscore.txt");
    if (high_score_file.is_open()) {
        high_score_file >> high_score;
        high_score_file.close();
    } else {
        high_score = 0;
    }
}

void Game::run() {
    while (true) {
        game_over = false;
        score = 0;
        level = 1;
        snake = Snake();
        food.respawn(snake.getBody());

        while (!game_over) {
            // Get user input
            Direction dir = input.getDirection();
            if (static_cast<int>(dir) != -1) {
                snake.setDirection(dir);
            }

            // Move the snake
            snake.move();

            // Check for collision with food
            Point head = snake.getBody()[0];
            Point food_pos = food.getPosition();
            if (head.x == food_pos.x && head.y == food_pos.y) {
                snake.grow();
                food.respawn(snake.getBody());
                score += 10;
                if (score > high_score) {
                    high_score = score;
                }
            }

            // Check for collision with walls
            if (head.x <= 0 || head.x >= board.getWidth() + 1 || head.y <= 0 || head.y >= board.getHeight() + 1) {
                game_over = true;
            }

            // Check for collision with self
            if (snake.checkSelfCollision()) {
                game_over = true;
            }

            // Check for level up
            if (snake.getBody().size() == (size_t)board.getWidth() * board.getHeight()) {
                level++;
                snake = Snake();
                mvprintw(board.getHeight() / 2, board.getWidth() / 2 - 6, "Level %d", level);
                refresh();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            // Clear the screen
            clear();

            // Draw the board, snake and food
            board.draw();
            snake.draw();
            food.draw();

            // Draw the score
            mvprintw(0, 2, "Score: %d", score);
            mvprintw(0, 20, "High Score: %d", high_score);
            mvprintw(0, 40, "Level: %d", level);

            // Refresh the screen
            refresh();

            // Add a delay to control game speed
            std::this_thread::sleep_for(std::chrono::milliseconds(100 - (level - 1) * 10));
        }

        // Game over UI
        mvprintw(board.getHeight() / 2, board.getWidth() / 2 - 5, "Game Over");
        mvprintw(board.getHeight() / 2 + 1, board.getWidth() / 2 - 8, "Final Score: %d", score);
        mvprintw(board.getHeight() / 2 + 2, board.getWidth() / 2 - 12, "Press any key to play again");
        refresh();
        nodelay(stdscr, FALSE);
        getch();
        nodelay(stdscr, TRUE);

        // Save high score
        std::ofstream high_score_file_out("highscore.txt");
        if (high_score_file_out.is_open()) {
            high_score_file_out << high_score;
            high_score_file_out.close();
        }
    }

    // Clean up and close PDCurses
    endwin();
}
