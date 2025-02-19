#include "Level.h"

Level::Level(int t_size) {
    this->tile_size = t_size;
}

void Level::CreateLevel(int width, int height) {
    this->level.resize(height, std::vector<std::shared_ptr<GameObject>>(width));
}

