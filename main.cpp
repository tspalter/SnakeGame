#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <fstream>

// Game settings
const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 25;

// Game state
bool gameOver;
int score;
int highScore = 0;
int x, y, fruitX, fruitY;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
std::vector<int> tailX, tailY;
int nTail;
int speed = 100; // Lower is faster

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showCursor(bool show) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = BOARD_WIDTH / 2;
    y = BOARD_HEIGHT / 2;
    fruitX = rand() % BOARD_WIDTH;
    fruitY = rand() % BOARD_HEIGHT;
    score = 0;
    nTail = 0;
    tailX.clear();
    tailY.clear();
    speed = 100;
}

void Draw() {
    system("cls"); // Clear the console

    // Top wall
    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (j == 0)
                std::cout << "#"; // Left wall

            if (i == y && j == x)
                std::cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                std::cout << "F"; // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o"; // Snake tail
                        printTail = true;
                    }
                }
                if (!printTail)
                    std::cout << " ";
            }

            if (j == BOARD_WIDTH - 1)
                std::cout << "#"; // Right wall
        }
        std::cout << std::endl;
    }

    // Bottom wall
    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    std::cout << "Score:" << score << "  High Score: " << highScore << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
        case 75: // Left arrow
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
        case 77: // Right arrow
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 72: // Up arrow
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 80: // Down arrow
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX.empty() ? x : tailX[0];
    int prevY = tailY.empty() ? y : tailY[0];
    int prev2X, prev2Y;
    if (!tailX.empty()) {
        tailX[0] = x;
        tailY[0] = y;
    }
     for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Wall collision
    if (x >= BOARD_WIDTH || x < 0 || y >= BOARD_HEIGHT || y < 0) {
        gameOver = true;
    }

    // Self collision
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Eat fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % BOARD_WIDTH;
        fruitY = rand() % BOARD_HEIGHT;
        nTail++;
        tailX.push_back(x);
        tailY.push_back(y);
    }
    
    // Level up
    if (nTail == BOARD_WIDTH * BOARD_HEIGHT) {
        // You win! Start new level
        score += 100;
        speed = max(10, speed - 10);
        nTail = 0;
        tailX.clear();
        tailY.clear();
        x = BOARD_WIDTH / 2;
        y = BOARD_HEIGHT / 2;
        fruitX = rand() % BOARD_WIDTH;
        fruitY = rand() % BOARD_HEIGHT;
    }
}

void GameOverScreen() {
    system("cls");
    std::cout << "GAME OVER" << std::endl;
    std::cout << "Score: " << score << std::endl;
    if (score > highScore) {
        highScore = score;
        saveHighScore();
        std::cout << "New High Score!" << std::endl;
    }
    std::cout << "High Score: " << highScore << std::endl;
    std::cout << "Play Again? (y/n)" << std::endl;
}


int main() {
    showCursor(false);
    srand(time(0));
    loadHighScore();

    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(speed);
        }
        GameOverScreen();
        std::cin >> choice;
    }

    return 0;
}