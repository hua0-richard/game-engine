#include "Collider.h"
#include "Character.h"
#include <cmath>

Collider::Collider() {}
Collider::~Collider() {}

void Collider::RegisterRigidBody(std::shared_ptr<GameObject> obj) {
    this->RigidBodies.push_back(obj);
}

void Collider::RegisterTransparentBody(std::shared_ptr<GameObject> obj) {
    this->TransparentBodies.push_back(obj);
}

void Collider::RegisterCharacterBody(std::shared_ptr<Character> character) {
    this->CharacterBodies.push_back(character);
}

void Collider::DetectCollisions() {
    for (int i = 0; i < CharacterBodies.size(); i++) {
        HandleCollisions(CharacterBodies[i]);
    }
}

void Collider::HandleCollisions(std::shared_ptr<Character> self) {
    if (!self) {
        return;
    }
    for (int i = 0; i < this->RigidBodies.size(); i++) {
        if (!this->RigidBodies[i] || this->RigidBodies[i].get() == self.get()) {
            continue;
        }
        if (std::abs(this->RigidBodies[i]->p_position.x - self->p_position.x) < 1 && 
            std::abs(this->RigidBodies[i]->p_position.y - self->p_position.y) < 1) {
            // self->Collision(this->RigidBodies[i]->p_position);
        }
    }

    for (int i = 0; i < this->TransparentBodies.size(); i++) {
        if (!this->TransparentBodies[i] || this->TransparentBodies[i].get() == self.get()) {
            continue;
        }
        if (std::abs(this->TransparentBodies[i]->p_position.x - self->p_position.x) < 1 && 
            std::abs(this->TransparentBodies[i]->p_position.y - self->p_position.y) < 1) {
            this->TransparentBodies[i]->Collision();
        }
    }

    for (int i = 0; i < this->CharacterBodies.size(); i++) {
        if (!this->CharacterBodies[i] || this->CharacterBodies[i].get() == self.get()) {
            continue;
        }
        if (std::abs(this->CharacterBodies[i]->p_position.x - self->p_position.x) < 1 && 
            std::abs(this->CharacterBodies[i]->p_position.y - self->p_position.y) < 1) {
        }
    }
}

bool Collider::Points(Vector2 p1, Vector2 p2) {
    int boxWidth = 1;
    int boxHeight = 1;

    // Check collision
    if (p2.x == p1.x && p2.y == p1.y) {
        std::cout << "collision" << std::endl;
        return true;
    }
    return false;
}


bool Collider::CheckRigidBodyCollisionsPlayer(Vector2 p1) {
    for (int i = 0; i < RigidBodies.size(); i++) {
        if (Points(p1, RigidBodies[i]->p_position)) {
            return true;
        }
    }
    return false;
}





