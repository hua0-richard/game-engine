#include "PowerPellet.h"

void PowerPellet::LoadSprite(int t_size) {
    float x = this->p_position.x * t_size;
    float y = this->p_position.y * t_size;
    DrawCircle(x + t_size / 2, y + t_size / 2, t_size / 4 , YELLOW);
}

void PowerPellet::DrawSelf(int t_size) {
    if (!consumed) {
        LoadSprite(t_size);
    }
}