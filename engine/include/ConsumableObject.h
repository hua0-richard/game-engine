#ifndef CONSUMABLE_OBJECT_H
#define CONSUMABLE_OBJECT_H

#include "GameObject.h"
#include <memory>
#include <vector>

class ConsumableObject : public GameObject {
    public: 
        bool consumed = false; 
        virtual void LoadSprite(int size_t = 0);
        void DrawSelf(int size_t) override;
        void Collision() override;
        bool GetConsumed(); 
};

#endif // CONSUMABLE_OBJECT_H