#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {}

void Enemy::SeekTarget(float x_pos, float y_pos) {
    this->m_position.x = x_pos - 1;
    this->m_position.y = y_pos - 1; 
}
