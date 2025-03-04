#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {}

void Enemy::SeekTarget(float x_pos, float y_pos) {
    // pass in game level and return an array
    // use target position and m position when the p psotion and m position are the same move on to the next position
    this->m_position.x = x_pos;
    this->m_position.y = y_pos;
}
