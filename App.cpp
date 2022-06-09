
#include "App.h"

void App::initGame() {
    this->framesCounter = 0;
    this->isGameOver = false;
    this->pause = false;

    this->offset.x = screenWidth % SQUARE_SIZE;
    this->offset.y = screenHeight % SQUARE_SIZE;

    for(int i = 0; i < SNAKE_LENGTH; i++){
        snake[i].setPosition({offset.x / 2, offset.y / 2});
        snake[i].setSize({SQUARE_SIZE, SQUARE_SIZE});
        snake[i].setSpeed({SQUARE_SIZE, 0});

        if(i == 0){
            snake[i].setColor(DARKPURPLE);
        } else {
            snake[i].setColor(PURPLE);
        }
    }

    for(auto & i : snakePosition){
        i = {0, 0};
    }

    food.setPosition({offset.x/2, offset.y/2});
    food.setSize({SQUARE_SIZE, SQUARE_SIZE});
    food.setColor(SKYBLUE);
    food.setIsActive(false);
}

void App::updateGame() {

}

void App::drawGame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if(!this->isGameOver){
        // draw grid lines
        for(int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++){
            DrawLineV({SQUARE_SIZE * i + offset.x / 2, offset.y / 2},
                      {SQUARE_SIZE * i + offset.x/2, screenHeight - offset.y/2}, LIGHTGRAY);
        }

        for(int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++){
            DrawLineV({ offset.x / 2, SQUARE_SIZE * i + offset.y / 2},
                      {screenWidth - offset.x/2,  SQUARE_SIZE * i + offset.y/2}, LIGHTGRAY);
        }

        // draw snake
        for(int i = 0; i < snake[0].getCounterTail(); i++){
            DrawRectangleV(snake[i].getPosition(), snake[i].getSize(), snake[i].getColor());
        }

        // draw food
        DrawRectangleV(food.getPosition(), food.getSize(), food.getColor());

        // TODO pause game
    }

    EndDrawing();

}

void App::run() {
    InitWindow(screenWidth, screenHeight, "Snake Game");

    // init game
    this->initGame();

    // set up window
    SetTargetFPS(60);

    // Main game loop
    while(!WindowShouldClose()){
        // update and draw ...
        this->updateGame();
        this->drawGame();
    }

    CloseWindow();
}

