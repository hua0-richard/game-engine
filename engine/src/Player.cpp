#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <memory>
#include <vector>

Player::Player() {
    this->m_position = {0.0f, 0.0f};
}

Player::~Player() {}

void Player::moveUp() {
    this->m_position.y += 1;
}

void Player::moveDown() {
    this->m_position.y -= 1;
}

void Player::moveLeft() {
    this->m_position.x -= 1;
}

void Player::moveRight() {
    this->m_position.x += 1;
}

void Player::DrawSelf(int t_size) {
    DrawCircle(this->m_position.x, this->m_position.y, t_size / 2, YELLOW);
}

