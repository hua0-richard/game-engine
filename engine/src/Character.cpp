#include "Character.h"  
#include <cmath>
#include <iostream>

Character::Character() {
    this->m_position = {0.0f, 0.0f};
    this->p_position = {0.0f, 0.0f};
    this->facing_angle = 0.0f;
}

Character::~Character() {}

void Character::moveUp() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y -= 1;
        this->facing_angle = 270.0f;
    }
}

void Character::moveDown() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y += 1;
        this->facing_angle = 90.0f;
    }   
}

void Character::moveLeft() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x -= 1;
        this->facing_angle = 180.0f;
    }   
}

void Character::moveRight() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x += 1;
        this->facing_angle = 0.0f;
    }    
}

void Character::updateAnimation() {
    // Base class has no animation state to update
}

void Character::updatePosition(int& p_x_fixed, int& p_y_fixed, int m_x_fixed, int m_y_fixed, int stepSize) {
    if (p_x_fixed > m_x_fixed) {
        p_x_fixed -= stepSize;
        if (p_x_fixed < m_x_fixed) p_x_fixed = m_x_fixed; 
    } else if (p_x_fixed < m_x_fixed) {
        p_x_fixed += stepSize;
        if (p_x_fixed > m_x_fixed) p_x_fixed = m_x_fixed; 
    }

    if (p_y_fixed > m_y_fixed) {
        p_y_fixed -= stepSize;
        if (p_y_fixed < m_y_fixed) p_y_fixed = m_y_fixed; 
    } else if (p_y_fixed < m_y_fixed) {
        p_y_fixed += stepSize;
        if (p_y_fixed > m_y_fixed) p_y_fixed = m_y_fixed;
    }
}

bool Character::isMoving(int p_x_fixed, int p_y_fixed, int m_x_fixed, int m_y_fixed) const {
    return p_x_fixed != m_x_fixed || p_y_fixed != m_y_fixed;
}

void Character::animate(float centerX, float centerY, float radius) {
    // Base animation is just a yellow circle
    DrawCircle(centerX, centerY, radius, YELLOW);
}


void Character::DrawSelf(int t_size) {
    const int scale = 1000; 
    const int stepSize = 100;

    // Calculate fixed-point positions
    int p_x_fixed = static_cast<int>(p_position.x * scale);
    int p_y_fixed = static_cast<int>(p_position.y * scale);
    int m_x_fixed = static_cast<int>(m_position.x * scale);
    int m_y_fixed = static_cast<int>(m_position.y * scale);

    // Update position with smooth movement
    updatePosition(p_x_fixed, p_y_fixed, m_x_fixed, m_y_fixed, stepSize);

    // Update actual position
    p_position.x = static_cast<float>(p_x_fixed) / scale;
    p_position.y = static_cast<float>(p_y_fixed) / scale;

    // Handle animation state
    if (isMoving(p_x_fixed, p_y_fixed, m_x_fixed, m_y_fixed)) {
        updateAnimation();
    }

    // Calculate drawing parameters
    float centerX = p_position.x * t_size + t_size / 2;
    float centerY = p_position.y * t_size + t_size / 2;
    float radius = t_size / 2;

    // Draw the character using the animation method
    animate(centerX, centerY, radius);
}

void Character::CharacterCollision(Vector2 pos) {
    this->collision = true;
    // this->m_position.y = pos.y - 1; 
}