#ifndef CONSUMABLE_OBJECT_H
#define CONSUMABLE_OBJECT_H

#include "GameObject.h"
#include <memory>
#include <vector>

class ConsumableObject : public GameObject {
    virtual void LoadSprite(int size_t = 0);
    void DrawSelf(int size_t) override;
};

#endif // CONSUMABLE_OBJECT_H