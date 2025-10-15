#ifndef SNAKE_H
#define SNAKE_H

#include "Point.h"
#include <vector>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake();
    void draw();
    void move();
    void setDirection(Direction dir);
    void grow();
    std::vector<Point> getBody();
    bool checkSelfCollision();

private:
    std::vector<Point> body;
    Direction direction;
};

#endif // SNAKE_H
