#ifndef CONSUMABLE_OBJECT_H
#define CONSUMABLE_OBJECT_H

#include "GameObject.h"
#include <memory>
#include <vector>

class ConsumableObject : GameObject {
    void DrawSelf(int size_t) override {};
};

#endif // CONSUMABLE_OBJECT_H