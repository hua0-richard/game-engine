#ifndef PACMAN_H
#define PACMAN_H

#include "Character.h"

class PacMan : public Character {
protected:
    float mouth_angle;
    bool is_mouth_opening;

    void updateAnimation() override;
    void animate(float centerX, float centerY, float radius) override;

public:
    PacMan();
};

#endif