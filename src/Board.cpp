#include "Board.h"
#include <curses.h>

Board::Board() {
    // Nothing to do here yet
}

void Board::draw() {
    // Draw top and bottom walls
    for (int i = 0; i < width + 2; ++i) {
        mvaddch(0, i, '*');
        mvaddch(height + 1, i, '*');
    }

    // Draw side walls
    for (int i = 0; i < height + 2; ++i) {
        mvaddch(i, 0, '*');
        mvaddch(i, width + 1, '*');
    }

    refresh();
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}
