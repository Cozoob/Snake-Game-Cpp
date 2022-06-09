

#ifndef SNAKE_GAME_CPP_POISON_H
#define SNAKE_GAME_CPP_POISON_H

#include "raylib.h"

class Poison {
private:
    Vector2 position;
    Vector2 size;
    bool isActive;
    Color color;
public:
    Poison() : position({0, 0}), size({0, 0}), isActive(false), color({RED}) {}

     // settery
    void setPosition(Vector2 pos){
        this->position = pos;
    }

    void setSize(Vector2 vector2){
        this->size = vector2;
    }

    void setIsActive(bool active){
        this->isActive = active;
    }

    // gettery
    Vector2 getPosition(){
        return this->position;
    }

    Vector2 getSize(){
        return this->size;
    }

    Color getColor(){
        return this->color;
    }

    bool getIsActive(){
        return this->isActive;
    }
};


#endif //SNAKE_GAME_CPP_POISON_H
