#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Character.h"
#include <memory>
#include <vector>
#include <string>

// Forward declaration
class Collider;

class Enemy : public Character {
private:
    float moveSpeed;       
    float maxTurnRate;      
    bool smoothMovement;   

public:
    Enemy();
    ~Enemy();

    // Movement methods
    void SeekTarget(int x_pos, int y_pos);
    void SetMoveSpeed(float speed);
    float GetMoveSpeed() const;
    void SetSmoothMovement(bool smooth);
    
    // Override DrawSelf to incorporate variable speed
    void DrawSelf(int t_size) override;
    
    // Animation method
    void animate(float centerX, float centerY, float radius) override;
};

#endif
