

#ifndef SNAKE_GAME_CPP_SNAKE_H
#define SNAKE_GAME_CPP_SNAKE_H

#define SNAKE_LENGTH 256

#include "raylib.h"

class Snake {
private:
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
    int counterTail;
    bool allowMove;
public:
    Snake() : position({0,0}), size({0,0}), speed({0,0}),
    color({'0', '0', '0', '0'}), counterTail(1), allowMove(false) {}

    Snake(Vector2 position, Vector2 size, Vector2 speed, Color color): position{position}, size{size},
    speed{speed}, color{color}, counterTail(1), allowMove(false) {}

    // settery
    void setCounterTail(int counter){
        this->counterTail = counter;
    }

    void setAllowMove(bool allowed){
        this->allowMove = allowed;
    }

    void setPosition(Vector2 vector2){
        this->position = vector2;
    }

    void setSize(Vector2 vector2){
        this->size = vector2;
    }

    void setSpeed(Vector2 vector2){
        this->speed = vector2;
    }

    void setColor(Color color){
        this->color = color;
    }

    // gettery
    Vector2 getPosition(){
        return this->position;
    }

    Vector2 getSize(){
        return this->size;
    }

    Vector2 getSpeed(){
        return this->speed;
    }

    Color getColor(){
        return this->color;
    }

    bool isAllowedToMove(){
        return this->allowMove;
    }
};


#endif //SNAKE_GAME_CPP_SNAKE_H
