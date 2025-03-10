#include "Enemy.h"
#include "Collider.h"
#include <cmath>
#include <iostream>

Enemy::Enemy() {
    // Initialize movement properties
    moveSpeed = 1.0f;       // Default speed in tiles per second
    maxTurnRate = 0.2f;     // Maximum turn rate (for smooth turns)
    smoothMovement = true;  // Enable smooth movement by default
}

Enemy::~Enemy() {
    // Destructor
}

void Enemy::SeekTarget(int x_pos, int y_pos) {
    // If smooth movement is enabled, apply some constraints
    if (smoothMovement) {
        // Calculate the difference between current and target position
        float dx = static_cast<float>(x_pos) - this->p_position.x;
        float dy = static_cast<float>(y_pos) - this->p_position.y;
        
        // Calculate distance to target
        float distance = std::sqrt(dx * dx + dy * dy);
        
        // If already at target or very close, just set it directly
        if (distance < 0.05f) {
            this->m_position.x = x_pos;
            this->m_position.y = y_pos;
            return;
        }
        
        // Calculate movement direction
        float dirX = dx / distance;
        float dirY = dy / distance;
        
        // Set the target position (will be smoothly approached in Character's updatePosition)
        this->m_position.x = x_pos;
        this->m_position.y = y_pos;
        
        // Update the facing angle based on movement direction
        this->facing_angle = std::atan2(dirY, dirX) * 57.2958f; // Convert to degrees
    } else {
        // Simple direct setting of target position
        this->m_position.x = x_pos;
        this->m_position.y = y_pos;
    }
}

void Enemy::SetMoveSpeed(float speed) {
    if (speed > 0.0f) {
        moveSpeed = speed;
    }
}

float Enemy::GetMoveSpeed() const {
    return moveSpeed;
}

void Enemy::SetSmoothMovement(bool smooth) {
    smoothMovement = smooth;
}

// Override the Character movement methods to incorporate variable speed
void Enemy::DrawSelf(int t_size) {
    const int scale = 10000;
    
    // Calculate step size based on move speed (higher speed = larger steps)
    // The base stepSize in Character is 1800, so we scale around that
    int stepSize = static_cast<int>(1800.0f * moveSpeed);
    
    // Make sure the step size isn't too small or too large
    if (stepSize < 100) stepSize = 100;
    if (stepSize > 5000) stepSize = 5000;

    // Calculate fixed-point positions
    int p_x_fixed = static_cast<int>(p_position.x * scale);
    int p_y_fixed = static_cast<int>(p_position.y * scale);
    int m_x_fixed = static_cast<int>(m_position.x * scale);
    int m_y_fixed = static_cast<int>(m_position.y * scale);

    // Update position with smooth movement using our custom step size
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

    // Draw the enemy using the animation method
    animate(centerX, centerY, radius);
}

void Enemy::animate(float centerX, float centerY, float radius) {
    // Draw a red circle for the enemy
    DrawCircle(centerX, centerY, radius, RED);
}


