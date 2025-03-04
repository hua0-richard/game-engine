#include "Level.h"

Level::Level(int t_size) {
    this->tile_size = t_size;
}

void Level::CreateLevel(int width, int height) {
    this->level.resize(height, std::vector<std::shared_ptr<GameObject>>(width));
}

void Level::AddGameObject(int row, int col, int t_size, std::shared_ptr<GameObject> obj) {
    obj->p_position.x = col;
    obj->p_position.y = row;
    obj->m_position = obj->p_position;
    level[row][col] = obj;
}

