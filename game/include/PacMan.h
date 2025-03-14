#ifndef PACMAN_H
#define PACMAN_H

#include "Player.h"
#include "GameObject.h"
#include <memory>
#include "Pause.h"
#include "Flee.h"

class Pacman : public Player {
    public: 
        Pacman();
        ~Pacman();
        void CollisionVisitor(std::shared_ptr<GameObject> obj) override; 
};

#endif