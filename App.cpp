
#include "App.h"

void App::initGame() {
    this->framesCounter = 0;
    this->isGameOver = false;
    this->pause = false;

    this->offset.x = screenWidth % SQUARE_SIZE;
    this->offset.y = screenHeight % SQUARE_SIZE;


}

void App::updateGame() {

}

void App::drawGame() {

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

