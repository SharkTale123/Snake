#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver = false;
int x, y;
int fruitX, fruitY;
const int height = 20;
const int width = 20;
enum eDirection {STOP, UP, DOWN, LEFT, RIGHT};
eDirection dir;
int score = 0;
int tailX[100], tailY[100];
int nTail = 0;

void Setup() {
    x = width / 2;
    y = height / 2;
    fruitX = rand() % 20;
    fruitY = (rand() % 19) + 1;
}

void Draw() {
    for (int i = 0; i < width; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "|";
            } else if (j == height-1) {
                cout << "|";
            } else if (j == x && i == y) {
                cout << "0";
            } else if (j == fruitX && i == fruitY) {
                cout << "F";
            } else {
                bool print = false;
                for(int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "Your Score is: " << score << endl;

}

void Input() {
    if (_kbhit()) {
        char ch = getch();
        switch(ch) {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        }
    }
}

void Logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    //if (x <= 0 || x >= width - 1 || y < 0 || y >= height) {
        //gameOver = true;
    //}

    if (x <= 0) {
        x = width-1;
    } else if (x >= width - 1) {
        x = 1;
    } else if (y >= height) {
        y = 0;
    } else if (y < 0) {
        y = height;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % 20;
        fruitY = (rand() % 19) + 1;
        nTail++;
    }

    for (int n = 0; n < nTail; n++) {
        if (tailX[n] == x && tailY[n] == y) {
            gameOver = true;
        }
    }
    if (prevX == x && prevY == y && nTail == 1) {
        gameOver = true;
    }
}

int main()
{
        Setup();
        while(gameOver == false) {
            system("cls");
            Draw();
            Input();
            Logic();
            Sleep(100);
        }
}
