#include "Pacman.h"
#include "Ghost.h"
#include "raylib.h"
#include "ConsumableObject.h"
#include "PowerPellet.h"
#include "Flee.h"
#include "Pathfinding.h"
#include "Pause.h"

Pacman::Pacman() {
    this->score = 0;
    this->lives = 1;
}
Pacman::~Pacman() {}

void Pacman::CollisionVisitor(std::shared_ptr<GameObject> obj) {
    if (auto ghost = std::dynamic_pointer_cast<Ghost>(obj)) {
        // CloseWindow();
        std::cout << "ghost" << std::endl;
    if (ghost->retreat == false){
        if (FLEE) {
            if (ghost->didRetreat == false) {
                ghost->retreat = true; 
                ghost->SetMoveSpeed(2.0f);
                ghost->didRetreat = true;
                ghost->flee = false;
            } else if (ghost->didRetreat == true) {
                PAUSE = true;
            }
            std::cout << "retreat" << std::endl;
        } else {
            PAUSE = true;
            std::cout << "dead" << std::endl; 
        }
    }
    } else if (auto powerPellet = std::dynamic_pointer_cast<PowerPellet>(obj)) {
        if (!powerPellet->GetConsumed()) {
            FLEE = false; 
            FLEE = true;
            powerPellet->consumed = true;
            std::cout << "power pellet" << std::endl;
            StartFleeTimer(300); // 10 seconds at 30 FPS
            this->score += 200;
        }
    }
    else if (auto consumable = std::dynamic_pointer_cast<ConsumableObject>(obj)) {
        if (!consumable->GetConsumed()) {
            consumable->consumed = true;
            std::cout << "pellet" << std::endl;
            this->score += 10; 
        }
    }
}