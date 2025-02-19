#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

Player::Player() {
    this->m_position = {0.0f, 0.0f};
    this->p_position = {0.0f, 0.0f};
}

Player::~Player() {}

void Player::moveUp() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y -= 1;
    }
    
}

void Player::moveDown() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y += 1;    }   
}

void Player::moveLeft() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x -= 1;
    }   
}

void Player::moveRight() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x += 1;
    }    
}

void Player::DrawSelf(int t_size) {
    const int scale = 1000; // Scale factor for fixed-point representation
    const int stepSize = 100; // Step size in fixed-point (0.2 * scale)

    // Convert positions to fixed-point
    int p_x_fixed = static_cast<int>(p_position.x * scale);
    int p_y_fixed = static_cast<int>(p_position.y * scale);
    int m_x_fixed = static_cast<int>(m_position.x * scale);
    int m_y_fixed = static_cast<int>(m_position.y * scale);

    // Move toward target position in fixed-point
    if (p_x_fixed > m_x_fixed) {
        p_x_fixed -= stepSize;
        if (p_x_fixed < m_x_fixed) p_x_fixed = m_x_fixed; // Snap to target
    } else if (p_x_fixed < m_x_fixed) {
        p_x_fixed += stepSize;
        if (p_x_fixed > m_x_fixed) p_x_fixed = m_x_fixed; // Snap to target
    }

    if (p_y_fixed > m_y_fixed) {
        p_y_fixed -= stepSize;
        if (p_y_fixed < m_y_fixed) p_y_fixed = m_y_fixed; // Snap to target
    } else if (p_y_fixed < m_y_fixed) {
        p_y_fixed += stepSize;
        if (p_y_fixed > m_y_fixed) p_y_fixed = m_y_fixed; // Snap to target
    }

    // Convert back to floating-point for rendering
    p_position.x = static_cast<float>(p_x_fixed) / scale;
    p_position.y = static_cast<float>(p_y_fixed) / scale;

    // Draw the circle at the updated position
    DrawCircle(p_position.x * t_size + t_size / 2, p_position.y * t_size + t_size / 2, t_size / 2, YELLOW);
}

