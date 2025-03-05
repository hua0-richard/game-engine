#include "Enemy.h"
#include "Collider.h"

Enemy::Enemy() {}
Enemy::~Enemy() {
    // Destructor
}

void Enemy::SeekTarget(float x_pos, float y_pos) {
    this->m_position.x = x_pos;
    this->m_position.y = y_pos;
}
