#include "Pacman.h"

Pacman::Pacman(Vector2 p_pos, int p_size) : GameObject(p_pos, p_size)
{

}

void Pacman::Update()
{

    Movement();
}

void Pacman::Draw()
{
    
}

Direction Pacman::GetMoveDirection()
{
    return Direction();
}

void Pacman::SetMoveDirection(Direction p_direction)
{

}

void Pacman::Movement()
{

}
