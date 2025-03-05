#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Character.h"
#include <memory>
#include <vector>

// Forward declaration
class Collider;

class Enemy : public Character {
    public:
        Enemy();
        ~Enemy();

        void SeekTarget(float x_pos, float y_pos);
};

#endif
