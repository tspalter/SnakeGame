#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Snake.h"
#include "Input.h"
#include "Food.h"

class Game {
public:
    Game();
    void run();
private:
    Board board;
    Snake snake;
    Input input;
    Food food;
    bool game_over;
    int score;
    int high_score;
    int level;
};

#endif // GAME_H
