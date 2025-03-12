#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <memory>
#include <vector>

class Player : public Character {
public:
    int score = 0;
    int lives = 1; 
    Player();
    ~Player();
};

#endif // PLAYER_H
