#include "Wall.h"

void Wall::LoadSprite(int t_size) {
    float x = this->p_position.x * t_size;
    float y = this->p_position.y * t_size;
    DrawRectangleLines(x, y, t_size, t_size, BLUE);
}