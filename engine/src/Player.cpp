#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <memory>
#include <vector>

Player::Player() {}

Player::~Player() {}

void Player::moveForward() {
    this->m_position.y += 1;
}

void Player::moveBackward() {
    this->m_position.y -= 1;
}

void Player::moveLeft() {
    this->m_position.x -= 1;
}

void Player::moveRight() {
    this->m_position.x += 1;
}

void Player::DrawSelf() {
    DrawCircle(400, 300, 50, BLUE);
}

