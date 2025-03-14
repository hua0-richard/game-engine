#ifndef COLLIDER_H
#define COLLIDER_H
#include <memory>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "raylib.h"

// Forward declaration of Character class
class Character;

class Collider {
    public: 
    Collider();
    ~Collider();

    std::vector<std::shared_ptr<GameObject>> RigidBodies;
    std::vector<std::shared_ptr<GameObject>> TransparentBodies;
    std::vector<std::shared_ptr<Character>> CharacterBodies; 

    void ValidNextMove(); 

    void RegisterCharacterBody(std::shared_ptr<Character> character); 
    void RegisterRigidBody(std::shared_ptr<GameObject> obj); 
    void RegisterTransparentBody(std::shared_ptr<GameObject> obj);
    void DetectCollisions();
    void HandleCollisions(std::shared_ptr<Character> Character);

    bool Points(Vector2 p1, Vector2 p2);
    bool CheckRigidBodyCollisionsPlayer(Vector2 p1);
};

#endif // COLLIDER_H
