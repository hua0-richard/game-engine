#include "ConsumableObject.h"

class PowerPellet : public ConsumableObject {
    void LoadSprite(int size_t) override; 
    void DrawSelf(int size_t) override; 
};