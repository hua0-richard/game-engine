#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include "GameObject.h"
#include <memory>
#include <vector>

class EnvironmentObject : public GameObject {
public:
    virtual void LoadSprite(int t_size = 0);
    void DrawSelf(int t_size) override;
};

#endif // ENVIRONMENT_OBJECT_H