#ifndef PACMAN_H
#define PACMAN_H

#include "Player.h"
#include "GameObject.h"
#include <memory>

class Pacman : public Player {
    public: 
        Pacman();
        ~Pacman();
        int score = 0; 
        void CollisionVisitor(std::shared_ptr<GameObject> obj) override; 
};

#endif