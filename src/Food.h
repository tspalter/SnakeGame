#ifndef FOOD_H
#define FOOD_H

#include "Point.h"
#include "Snake.h"

class Food {
public:
    Food(int board_width, int board_height);
    void draw();
    void respawn(const std::vector<Point>& snake_body);
    Point getPosition();

private:
    Point position;
    int board_width;
    int board_height;
};

#endif // FOOD_H
