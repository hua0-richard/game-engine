#include "Enemy.h"
#include "Collider.h"

Enemy::Enemy() {}
Enemy::~Enemy() {
    // Destructor
}

void Enemy::SeekTarget(int x_pos, int y_pos) {
    this->m_position.x = x_pos;
    this->m_position.y = y_pos;
}

void Enemy::animate(float centerX, float centerY, float radius) {
    // Base animation is just a yellow circle
    DrawCircle(centerX, centerY, radius, RED);
}


