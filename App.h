
#ifndef SNAKE_GAME_CPP_APP_H
#define SNAKE_GAME_CPP_APP_H

#define SQUARE_SIZE 30

#include "Snake.h"
#include "Food.h"

class App {
private:
    int screenWidth;
    int screenHeight;
    Snake snake[SNAKE_LENGTH];
    Food food;
    int framesCounter;
    bool isGameOver;
    bool pause;
    Vector2 offset = {0};
public:
    App(): screenHeight(450), screenWidth(800), snake(), food(), framesCounter(), isGameOver(), pause() {}

    void run();

private:
    void initGame();

    void updateGame();

    void drawGame();
};


#endif //SNAKE_GAME_CPP_APP_H
