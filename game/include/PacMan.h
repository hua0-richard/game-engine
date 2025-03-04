#ifndef PACMAN_H
#define PACMAN_H

#include "Player.h"

class Pacman : public Player {
    public: 
        Pacman();
        ~Pacman();
        int score = 0; 
};

#endif