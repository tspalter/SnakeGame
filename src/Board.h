#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    Board();
    void draw();
    int getWidth();
    int getHeight();

private:
    const int width = 40;
    const int height = 30;
};

#endif // BOARD_H
