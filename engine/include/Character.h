#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Collider.h"

class Character : public GameObject {
protected:
    // Vector2 m_position;
    // Vector2 p_position;
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

    bool collision = false;

    Character();
    virtual ~Character();
    void DrawSelf(int size_t) override; 
    void Collision(Vector2 pos);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();


};

#endif
