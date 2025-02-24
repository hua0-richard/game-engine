#ifndef CHARACTER_H // Check if CHARACTER_H has not been defined
#define CHARACTER_H // Define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject {
protected:
    Vector2 m_position;
    Vector2 p_position;
    float facing_angle;

    // Animation related methods that can be overridden
    virtual void updateAnimation();
    virtual void animate(float centerX, float centerY, float radius);
    
    // Helper methods
    void updatePosition(int& p_x_fixed, int& p_y_fixed, int m_x_fixed, int m_y_fixed, int stepSize);
    bool isMoving(int p_x_fixed, int p_y_fixed, int m_x_fixed, int m_y_fixed) const;

public: 
    enum Action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ATTACK,
        DEFEND
    };

    Character();
    virtual ~Character();
    void DrawSelf(int size_t) override; 

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Getter methods
    float GetX() const { return p_position.x; }
    float GetY() const { return p_position.y; }
    Vector2 GetPosition() const { return p_position; }
};

#endif
