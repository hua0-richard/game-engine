#include "ConsumableObject.h"

void ConsumableObject::Collision() {
    // this->consumed = true; 
}


void ConsumableObject::LoadSprite(int t_size) {
    float x = this->p_position.x * t_size;
    float y = this->p_position.y * t_size;
    DrawCircle(x + t_size / 2, y + t_size / 2, t_size / 8 , YELLOW);
}

void ConsumableObject::DrawSelf(int t_size) {
    if (!consumed) {
        LoadSprite(t_size); 
    }
}

bool ConsumableObject::GetConsumed() {
    return this->consumed;
}

