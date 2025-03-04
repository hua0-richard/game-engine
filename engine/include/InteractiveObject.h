#ifndef INTERACTIVE_OBJECT_H
#define INTERACTIVE_OBJECT_H

#include "GameObject.h"
#include <memory>
#include <vector>

class InteractiveObject : GameObject {
    void DrawSelf(int size_t) override {};
};

#endif // INTERACTIVE_OBJECT_H