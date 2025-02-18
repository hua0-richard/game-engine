#pragma once
#include "GameObject.h"

enum class Direction
{
    RIGHT, 
    LEFT, 
    UP, 
    DOWN
};

class Pacman : public GameObject
{
public:
    Pacman(Vector2 p_pos, int p_size);
    virtual ~Pacman() = default;

    void Update() override;
    void Draw() override;

    Direction GetMoveDirection();
    void SetMoveDirection(Direction p_direction);

private:
    void Movement();
    
    Direction moveDirection;
    int posX;
    int posY;
    int speed;
    

};