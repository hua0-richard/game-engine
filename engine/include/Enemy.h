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

    public:
        Enemy();
        ~Enemy();

        void SeekTarget(int x_pos, int y_pos);
        // virtual void animate(float centerX, float centerY, float radius) override;

};

#endif
