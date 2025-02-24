#include "Player.h"
#include "PacMan.h"


// Pacman::Pacman(Vector2 p_pos, int p_size) : Player(p_pos, p_size)
// {

// }

// void Pacman::Update()
// {

//     Movement();
// }

// void Pacman::Draw()
// {
    
// }

// Direction Pacman::GetMoveDirection()
// {
//     return Direction();
// }

// void Pacman::SetMoveDirection(Direction p_direction)
// {

// }

// void Pacman::Movement()
// {

// }

PacMan::PacMan() : Character() {
    mouth_angle = 0.0f;
    is_mouth_opening = true;
}

void PacMan::updateAnimation() {
    const float MOUTH_SPEED = 5.0f;
    const float MAX_MOUTH_ANGLE = 45.0f;
    
    if (is_mouth_opening) {
        mouth_angle += MOUTH_SPEED;
        if (mouth_angle >= MAX_MOUTH_ANGLE) {
            mouth_angle = MAX_MOUTH_ANGLE;
            is_mouth_opening = false;
        }
    } else {
        mouth_angle -= MOUTH_SPEED;
        if (mouth_angle <= 0) {
            mouth_angle = 0;
            is_mouth_opening = true;
        }
    }
}

void PacMan::animate(float centerX, float centerY, float radius) {
    // First call base class animation to draw the yellow circle
    Character::animate(centerX, centerY, radius);

    // Then add the mouth animation
    if (mouth_angle > 0) {
        DrawCircleSector(
            Vector2{centerX, centerY},
            radius,
            facing_angle - mouth_angle - 180,
            facing_angle + mouth_angle - 180,
            32,
            BLACK
        );
    }
}
