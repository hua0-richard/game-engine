#include "Level.h"

void Level::CreateLevel(int width, int height) {
    this->level.resize(height, std::vector<std::shared_ptr<GameObject>>(width));
}

