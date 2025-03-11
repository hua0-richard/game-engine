#include "Character.h"  
#include <cmath>
#include <iostream>

Character::Character() {
    this->m_position = {0.0f, 0.0f};
    this->p_position = {0.0f, 0.0f};
    this->facing_angle = 0.0f;
    this->cachedTexture = { 0 }; // Initialize with empty texture
    this->textureLoaded = false;
}

Character::~Character() {
    // Clean up the cached texture when the character is destroyed
    if (textureLoaded && cachedTexture.id != 0) {
        UnloadTexture(cachedTexture);
    }
}

void Character::loadResource(char* resource) {
    this->resource = resource;
}

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
    // Calculate distance to target
    int dx = m_x_fixed - p_x_fixed;
    int dy = m_y_fixed - p_y_fixed;
    
    // If we're very close to the target, just snap to it
    const int snapThreshold = 100; // Arbitrary small value
    
    if (std::abs(dx) <= snapThreshold && std::abs(dy) <= snapThreshold) {
        p_x_fixed = m_x_fixed;
        p_y_fixed = m_y_fixed;
        return;
    }
    
    // X-axis movement
    if (dx > 0) {
        // Moving right
        p_x_fixed += std::min(stepSize, dx);
    } else if (dx < 0) {
        // Moving left
        p_x_fixed -= std::min(stepSize, -dx);
    }
    
    // Y-axis movement
    if (dy > 0) {
        // Moving down
        p_y_fixed += std::min(stepSize, dy);
    } else if (dy < 0) {
        // Moving up
        p_y_fixed -= std::min(stepSize, -dy);
    }
}

bool Character::isMoving(int p_x_fixed, int p_y_fixed, int m_x_fixed, int m_y_fixed) const {
    return p_x_fixed != m_x_fixed || p_y_fixed != m_y_fixed;
}

void Character::animate(float centerX, float centerY, float radius) {
    // Base animation is just a yellow circle
    if (this->resource == nullptr) {
        DrawCircle(centerX, centerY, radius, YELLOW);
    } else {
        // Load texture only if it hasn't been loaded yet
        if (!textureLoaded) {
            cachedTexture = LoadTexture(this->resource);
            textureLoaded = true;
        }
        
        // Only draw if the texture was loaded successfully
        if (cachedTexture.id != 0) {
            DrawTexture(cachedTexture, centerX - radius, centerY - radius, WHITE);
        } else {
            // Fallback if texture couldn't be loaded
            DrawCircle(centerX, centerY, radius, YELLOW);
        }
    }
}

void Character::DrawSelf(int t_size) {
    // Use a larger scale for more precise fixed-point calculations
    const int scale = 100000; 
    
    // Calculate optimal step size based on desired speed
    // This will make character movement consistent regardless of frame rate
    const float moveSpeed = 5.0f; // Tiles per second
    const float deltaTime = GetFrameTime(); // Get time since last frame in seconds
    const int stepSize = static_cast<int>(moveSpeed * scale * deltaTime);
    
    // Calculate fixed-point positions
    int p_x_fixed = static_cast<int>(p_position.x * scale);
    int p_y_fixed = static_cast<int>(p_position.y * scale);
    int m_x_fixed = static_cast<int>(m_position.x * scale);
    int m_y_fixed = static_cast<int>(m_position.y * scale);
    
    // Store previous position for collision detection
    int prev_p_x_fixed = p_x_fixed;
    int prev_p_y_fixed = p_y_fixed;

    // Update position with smooth movement
    updatePosition(p_x_fixed, p_y_fixed, m_x_fixed, m_y_fixed, stepSize);

    // Handle collision - if collision flag is set, revert the movement
    if (collision) {
        p_x_fixed = prev_p_x_fixed;
        p_y_fixed = prev_p_y_fixed;
        collision = false; // Reset collision flag
    }

    // Update actual position with improved precision
    p_position.x = static_cast<float>(p_x_fixed) / scale;
    p_position.y = static_cast<float>(p_y_fixed) / scale;

    // Handle animation state
    if (isMoving(p_x_fixed, p_y_fixed, m_x_fixed, m_y_fixed)) {
        updateAnimation();
    }

    // Calculate drawing parameters with improved precision
    float centerX = p_position.x * t_size + t_size / 2.0f;
    float centerY = p_position.y * t_size + t_size / 2.0f;
    float radius = t_size / 2.0f;

    // Draw the character using the animation method
    animate(centerX, centerY, radius);
    
    // Debug visualization (optional)
    // DrawLine(centerX, centerY, m_position.x * t_size + t_size/2, m_position.y * t_size + t_size/2, BLACK);
}

void Character::CharacterCollision(Vector2 pos) {
    this->collision = true;
    // this->m_position.y = pos.y - 1; 
}

void Character::CollisionVisitor(std::shared_ptr<GameObject> obj) {}
