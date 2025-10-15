#include "Snake.h"
#include <curses.h>

Snake::Snake() {
    // Start the snake in the middle of the board
    int startX = 10;
    int startY = 10;

    // Initialize the snake with 3 segments
    body.push_back({startX, startY});
    body.push_back({startX - 1, startY});
    body.push_back({startX - 2, startY});

    direction = Direction::RIGHT;
}

void Snake::draw() {
    // Draw the head
    mvaddch(body[0].y, body[0].x, '@');

    // Draw the body
    for (size_t i = 1; i < body.size(); ++i) {
        mvaddch(body[i].y, body[i].x, '#');
    }
}

void Snake::setDirection(Direction dir) {
    // Prevent the snake from reversing
    if ((direction == Direction::UP && dir != Direction::DOWN) ||
        (direction == Direction::DOWN && dir != Direction::UP) ||
        (direction == Direction::LEFT && dir != Direction::RIGHT) ||
        (direction == Direction::RIGHT && dir != Direction::LEFT)) {
        direction = dir;
    }
}

void Snake::move() {
    Point newHead = body[0];

    switch (direction) {
        case Direction::UP:
            newHead.y--;
            break;
        case Direction::DOWN:
            newHead.y++;
            break;
        case Direction::LEFT:
            newHead.x--;
            break;
        case Direction::RIGHT:
            newHead.x++;
            break;
    }

    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
}

std::vector<Point> Snake::getBody() {
    return body;
}

bool Snake::checkSelfCollision() {
    Point head = body[0];
    for (size_t i = 1; i < body.size(); ++i) {
        if (head.x == body[i].x && head.y == body[i].y) {
            return true;
        }
    }
    return false;
}

