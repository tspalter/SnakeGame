#include "Food.h"
#include <curses.h>
#include <cstdlib>
#include <ctime>

Food::Food(int board_width, int board_height) : board_width(board_width), board_height(board_height) {
    srand(time(0));
    respawn({});
}

void Food::draw() {
    mvaddch(position.y, position.x, '*');
}

void Food::respawn(const std::vector<Point>& snake_body) {
    while (true) {
        bool on_snake = false;
        position.x = (rand() % board_width) + 1;
        position.y = (rand() % board_height) + 1;

        for (const auto& segment : snake_body) {
            if (segment.x == position.x && segment.y == position.y) {
                on_snake = true;
                break;
            }
        }

        if (!on_snake) {
            break;
        }
    }
}

Point Food::getPosition() {
    return position;
}
