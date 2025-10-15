#include "Input.h"
#include <curses.h>

Direction Input::getDirection() {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
        case 'w':
            return Direction::UP;
        case KEY_DOWN:
        case 's':
            return Direction::DOWN;
        case KEY_LEFT:
        case 'a':
            return Direction::LEFT;
        case KEY_RIGHT:
        case 'd':
            return Direction::RIGHT;
        default:
            // Return the current direction if no valid key is pressed
            return static_cast<Direction>(-1);
    }
}
