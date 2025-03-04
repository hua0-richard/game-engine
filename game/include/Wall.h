#ifndef WALL_H
#define WALL_H

#include "EnvironmentObject.h"

class Wall : public EnvironmentObject {
public:
    void LoadSprite(int t_size = 0) override;
};

#endif // WALL_H