
#ifndef SNAKE_GAME_CPP_APP_H
#define SNAKE_GAME_CPP_APP_H

#define SQUARE_SIZE 30
#define NUM_POISON 3

#include "Snake.h"
#include "Food.h"
#include "Poison.h"

class App {
private:
    int screenWidth;
    int screenHeight;
    Snake snake[SNAKE_LENGTH];
    Food food;
    Poison poison[NUM_POISON];
    int framesCounter;
    bool isGameOver;
    bool pause;
    Vector2 offset = {0};
    Vector2 snakePosition[SNAKE_LENGTH] = {0};
    int foodCounter;
public:
    App(): screenHeight(450), screenWidth(800), snake(), food(), poison(), framesCounter(), isGameOver(), pause(),
    foodCounter() {}

    void run();

private:
    void initGame();

    void updateGame();

    void drawGame();

    void drawGameOver();

    void drawInitialMessage();

    Vector2 getRandomPosition();
};


#endif //SNAKE_GAME_CPP_APP_H
