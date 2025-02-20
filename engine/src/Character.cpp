#include "Character.h" 

Character::Character() {
    this->m_position = {0.0f, 0.0f};
    this->p_position = {0.0f, 0.0f};
}

Character::~Character() {}

void Character::moveUp() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y -= 1;
    }
    
}

void Character::moveDown() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.y += 1;    }   
}

void Character::moveLeft() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x -= 1;
    }   
}

void Character::moveRight() {
    if (p_position.x == m_position.x && p_position.y == m_position.y) {
        this->m_position.x += 1;
    }    
}


void Character::DrawSelf(int t_size) {
    const int scale = 1000; 
    const int stepSize = 100;

    int p_x_fixed = static_cast<int>(p_position.x * scale);
    int p_y_fixed = static_cast<int>(p_position.y * scale);
    int m_x_fixed = static_cast<int>(m_position.x * scale);
    int m_y_fixed = static_cast<int>(m_position.y * scale);

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

    p_position.x = static_cast<float>(p_x_fixed) / scale;
    p_position.y = static_cast<float>(p_y_fixed) / scale;

    DrawCircle(p_position.x * t_size + t_size / 2, p_position.y * t_size + t_size / 2, t_size / 2, YELLOW);
}