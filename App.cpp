
#include <unistd.h>
#include <iostream>
#include "App.h"

void App::initGame() {
    this->framesCounter = 0;
    this->isGameOver = true;
    this->pause = false;

    snake[0].setCounterTail(1);
    snake[0].setAllowMove(false);

    this->offset.x = screenWidth % SQUARE_SIZE;
    this->offset.y = screenHeight % SQUARE_SIZE;

    for(int i = 0; i < SNAKE_LENGTH; i++){
        snake[i].setPosition({offset.x / 2, offset.y / 2});
        snake[i].setSize({SQUARE_SIZE, SQUARE_SIZE});
        snake[i].setSpeed({SQUARE_SIZE , 0});

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
    if(!this->isGameOver){
        if(IsKeyPressed('P')){
            this->pause = !pause;
        }

        if(!this->pause){
            // plater control

            if(IsKeyPressed(KEY_RIGHT) && (snake[0].getSpeed().x == 0) && snake[0].isAllowedToMove()){
                snake[0].setSpeed({SQUARE_SIZE, 0});
                snake[0].setAllowMove(false);
            }
            if(IsKeyPressed(KEY_LEFT) && (snake[0].getSpeed().x == 0) && snake[0].isAllowedToMove()){
                snake[0].setSpeed({-SQUARE_SIZE, 0});
                snake[0].setAllowMove(false);
            }
            if(IsKeyPressed(KEY_UP) && (snake[0].getSpeed().y == 0) && snake[0].isAllowedToMove()){
                snake[0].setSpeed({0, -SQUARE_SIZE});
                snake[0].setAllowMove(false);
            }
            if(IsKeyPressed(KEY_DOWN) && (snake[0].getSpeed().y == 0) && snake[0].isAllowedToMove()){
                snake[0].setSpeed({0, SQUARE_SIZE});
                snake[0].setAllowMove(false);
            }

            // snake movement
            for(int i = 0; i < snake[0].getCounterTail(); i++){
                snakePosition[i] = snake[i].getPosition();
            }

            if((framesCounter % 8) == 0){
                framesCounter = 0;
                for(int i = 0; i < snake[0].getCounterTail(); i++){
                    if(i == 0){
                        float x = snake[0].getPosition().x + snake[0].getSpeed().x;
                        float y = snake[0].getPosition().y + snake[0].getSpeed().y;
                        snake[0].setPosition({x, y});
                        snake[0].setAllowMove(true);
                    } else {
                        snake[i].setPosition(snakePosition[i - 1]);
                    }
                }
            }

            // wall behaviour
            if(((snake[0].getPosition().x > screenWidth - offset.x)) ||
                    (snake[0].getPosition().y > screenHeight - offset.y) ||
                    (snake[0].getPosition().x < 0) || snake[0].getPosition().y < 0){
                isGameOver = true;
            }

            // collision with yourself
            for(int i = 1; i < snake[0].getCounterTail(); i++){
                if((snake[0].getPosition().x == snake[i].getPosition().x) &&
                (snake[0].getPosition().y == snake[i].getPosition().y)){
                    isGameOver = true;
                }
            }

            // food position calc
            if(!food.getIsActive()){
                food.setIsActive(true);
                food.setPosition({GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2,
                                  GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2});

                for(int i = 0; i < snake[0].getCounterTail(); i++){
                    while(food.getPosition().x == snake[i].getPosition().x && food.getPosition().y == snake[i].getPosition().y){
                        food.setPosition({GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2,
                                          GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2});
                        i = 0;
                    }
                }
            }

            // collision
            if(snake[0].getPosition().x < (food.getPosition().x + food.getSize().x) && (snake[0].getPosition().x + snake[0].getSize().x) > food.getPosition().x &&
                    snake[0].getPosition().y < (food.getPosition().y + food.getSize().y) && (snake[0].getPosition().y + snake[0].getSize().y) > food.getPosition().y){
                int tail = snake[0].getCounterTail();
                snake[tail].getPosition() = snakePosition[tail - 1];
                snake[0].setCounterTail(tail + 1);
                food.setIsActive(false);
            }

            framesCounter++;
        }
    } else {
        if(IsKeyPressed(KEY_ENTER)){
            this->initGame();
            isGameOver = false;
        }
    }
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

void App::drawInstructions() {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Instrucions!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}

