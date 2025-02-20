#ifndef CHARACTER_H // Check if CHARACTER_H has not been defined
#define CHARACTER_H // Define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject {
public: 
    enum Action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ATTACK,
        DEFEND
    };

    Character();
    ~Character();
    void DrawSelf(int size_t) override; 

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif
