
#ifndef SNAKE_GAME_CPP_FOOD_H
#define SNAKE_GAME_CPP_FOOD_H

#include "raylib.h"

class Food {
private:
    Vector2 position;
    Vector2 size;
    bool isActive;
    Color color;
public:
    Food() : position({0,0}), size({0, 0}), isActive(false), color({'0', '0', '0', '0'}) {}

    Food(Vector2 position, Vector2 size, bool isActive, Color color): position{position}, size{size},
    isActive{isActive}, color{color} {}


    // gettery
    Vector2 getPosition(){
        return this->position;
    }

    Vector2 getSize(){
        return this->size;
    }

    bool getIsActive(){
        return this->isActive;
    }
};


#endif //SNAKE_GAME_CPP_FOOD_H
