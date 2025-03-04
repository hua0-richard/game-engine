#include "EnvironmentObject.h"
void EnvironmentObject::DrawSelf(int t_size) {
    float x = this->p_position.x * t_size;
    float y = this->p_position.y * t_size;
    DrawCircle(x, y, t_size, RED);
}
