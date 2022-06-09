

#ifndef SNAKE_GAME_CPP_SNAKE_H
#define SNAKE_GAME_CPP_SNAKE_H

#include "raylib.h"

class Snake {
private:
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
public:
    Snake() : position({0,0}), size({0,0}), speed({0,0}),
    color({'0', '0', '0', '0'}) {}

    Snake(Vector2 position, Vector2 size, Vector2 speed, Color color): position{position}, size{size},
    speed{speed}, color{color} {}


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
};


#endif //SNAKE_GAME_CPP_SNAKE_H
