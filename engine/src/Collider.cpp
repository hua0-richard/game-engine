#include "Collider.h"
#include "Character.h"
#include <cmath>

Collider::Collider() {}
Collider::~Collider() {}

void Collider::RegisterRigidBody(std::shared_ptr<GameObject> obj) {
    this->RigidBodies.push_back(obj);
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
        if (std::abs(this->RigidBodies[i]->p_position.x - self->p_position.x) <= 1 && 
            std::abs(this->RigidBodies[i]->p_position.y - self->p_position.y) <= 1) {
            self->Collision(this->RigidBodies[i]->p_position);
            std::cout << "collision detected - movement stopped" << std::endl;
        }
    }
}

