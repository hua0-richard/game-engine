#ifndef COLLIDER_H
#define COLLIDER_H
#include <memory>
#include <iostream>
#include "GameObject.h"
#include "Character.h"

// Empty file for now
class Collider {
    public: 
    Collider();
    ~Collider();

    std::vector<std::shared_ptr<GameObject>> RigidBodies;
    std::vector<std::shared_ptr<Character>> CharacterBodies; 

    void RegisterCharacterBody(std::shared_ptr<Character> character); 
    void RegisterRigidBody(std::shared_ptr<GameObject> obj); 
    void DetectCollisions();
    void HandleCollisions(std::shared_ptr<Character> self);
};

#endif // COLLIDER_H
