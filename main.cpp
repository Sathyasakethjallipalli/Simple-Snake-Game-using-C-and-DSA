#include <iostream>
#include <conio.h>
#include <windows.h>
#include <deque>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 15;

int x, y, fruitX, fruitY, score;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

deque<pair<int, int> > snake;

void Setup() {
    gameOver = false;
    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

    snake.clear();
    snake.push_front({x, y});
}

void Draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << "#";

        for (int j = 0; j < width; j++) {

            if (i == y && j == x)
                cout << "O";

            else if (i == fruitY && j == fruitX)
                cout << "F";

            else {
                bool printed = false;

                for (auto part : snake) {
                    if (part.first == j && part.second == i) {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }

                if (!printed)
                    cout << " ";
            }
        }

        cout << "#" << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    cout << "Score: " << score << endl;
    cout << "Controls: W = Up, S = Down, A = Left, D = Right" << endl;
}

void Input() {
    if (_kbhit()) {

        switch (_getch()) {

        case 'a':
        case 'A':
            if (dir != RIGHT)
                dir = LEFT;
            break;

        case 'd':
        case 'D':
            if (dir != LEFT)
                dir = RIGHT;
            break;

        case 'w':
        case 'W':
            if (dir != DOWN)
                dir = UP;
            break;

        case 's':
        case 'S':
            if (dir != UP)
                dir = DOWN;
            break;

        case 'x':
        case 'X':
            gameOver = true;
            break;
        }
    }
}

void Logic() {

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

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y)
            gameOver = true;
    }

    snake.push_front({x, y});

    if (x == fruitX && y == fruitY) {
        score += 10;

        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else {
        snake.pop_back();
    }
}

int main() {

    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    cout << endl << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}
