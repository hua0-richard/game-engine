#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Collider.h"

class Character : public GameObject {
protected:
    char* resource = nullptr;
    // Vector2 m_position;
    // Vector2 p_position;
    float facing_angle;
    Texture2D cachedTexture;    // Cached texture to avoid reloading
    bool textureLoaded = false; // Flag to track if texture is loaded

    // Animation related methods that can be overridden
    virtual void updateAnimation();
    
    // Helper methods
    void updatePosition(int& p_x_fixed, int& p_y_fixed, int m_x_fixed, int m_y_fixed, int stepSize);
    bool isMoving(int p_x_fixed, int p_y_fixed, int m_x_fixed, int m_y_fixed) const;

public: 
    virtual void loadResource(char* resource);
    virtual void animate(float centerX, float centerY, float radius);

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
    void CharacterCollision(Vector2 pos);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

};

#endif
