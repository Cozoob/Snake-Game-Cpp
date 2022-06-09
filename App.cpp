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

    for(int i = 0; i < NUM_POISON; i++){
        poison[i].setPosition({offset.x / 2, offset.y / 2});
        poison[i].setSize({SQUARE_SIZE, SQUARE_SIZE});
        poison[i].setIsActive(false);
    }
}

void App::updateGame() {
    if(!this->isGameOver){
        if(IsKeyPressed('P')){
            this->pause = !pause;
        }

        if(!this->pause){
            // player control

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
            float headX = snake[0].getPosition().x;
            float headY = snake[0].getPosition().y;

            if(headX > screenWidth - offset.x){
                headX = offset.x / 2;
            }

            if(headY > screenHeight - offset.y){
                headY = offset.y / 2;
            }

            if(headX < 0){
                headX = screenWidth - offset.x;
            }

            if(headY < 0){
                headY = screenHeight - offset.y;
            }

            snake[0].setPosition({headX, headY});

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
                food.setPosition(getRandomPosition());

                for(int i = 0; i < snake[0].getCounterTail(); i++){
                    while(food.getPosition().x == snake[i].getPosition().x &&
                    food.getPosition().y == snake[i].getPosition().y){
                        food.setPosition(getRandomPosition());
                        i = 0;
                    }
                }
            }

            // poison position calc
            for(int i = 0; i < NUM_POISON; i++){
                bool changePosition = false;
                if(foodCounter == 5){
                    foodCounter = 0;
                    changePosition = true;
                }

                if(!poison[i].getIsActive() || changePosition){
                    poison[i].setIsActive(true);
                    poison[i].setPosition(getRandomPosition());

                    for(int j = 0; j < snake[0].getCounterTail(); j++){
                        while(poison[i].getPosition().x == snake[j].getPosition().x &&
                        poison[i].getPosition().y == snake[j].getPosition().y){
                            poison[i].setPosition(getRandomPosition());
                            i = 0;
                        }
                    }
                }
            }

            // food collision
            if(snake[0].getPosition().x < (food.getPosition().x + food.getSize().x) &&
                    (snake[0].getPosition().x + snake[0].getSize().x) > food.getPosition().x &&
                    snake[0].getPosition().y < (food.getPosition().y + food.getSize().y) &&
                            (snake[0].getPosition().y + snake[0].getSize().y) > food.getPosition().y){
                int tail = snake[0].getCounterTail();
                snake[tail].getPosition() = snakePosition[tail - 1];
                snake[0].setCounterTail(tail + 1);
                food.setIsActive(false);
                foodCounter++;
            }

            // poison collision
            for(int i = 0; i < NUM_POISON; i++){
                if(snake[0].getPosition().x < (poison[i].getPosition().x + poison[i].getSize().x) &&
                        (snake[0].getPosition().x + snake[0].getSize().x) > poison[i].getPosition().x &&
                        snake[0].getPosition().y < (poison[i].getPosition().y + poison[i].getSize().y) &&
                        (snake[0].getPosition().y + snake[0].getSize().y) > poison[i].getPosition().y){
                    int tail = snake[0].getCounterTail();
                    if(tail == 1){
                        isGameOver = true;
                        break;
                    }

                    snake[tail].getPosition() = snakePosition[tail + 1];
                    snake[0].setCounterTail(tail - 1);
                    poison[i].setIsActive(false);
                }
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

        // draw poisons
        for(int i = 0; i < NUM_POISON; i++){
            DrawRectangleV(poison[i].getPosition(), poison[i].getSize(), poison[i].getColor());
        }

    } else {
        this->drawGameOver();
    }

    EndDrawing();
}

void App::run() {
    InitWindow(screenWidth, screenHeight, "Snake Game");

    // initial window
    while(!IsKeyPressed(KEY_ENTER)){
        this->drawInitialMessage();
    }

    // instructions how to play
    while(!IsKeyPressed(KEY_ENTER)){
        this->drawGameOver();
    }

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

void App::drawGameOver(){
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("GAME OVER! [ENTER] - to play again", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}

void App::drawInitialMessage() {
    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Welcome to Snake Game made by Marcin Kozub!", 180, 160, 20, LIGHTGRAY);
        DrawText("Use arrows to move snake, P - Pause game, ESP - exit", 130, 240, 20, LIGHTGRAY);
        DrawText("Click [ENTER] to start the game!", 220, 280, 20, LIGHTGRAY);

    EndDrawing();
}

Vector2 App::getRandomPosition() {
    return Vector2({GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2,
                    GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2});
}

