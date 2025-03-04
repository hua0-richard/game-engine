#ifndef LEVEL_H
#define LEVEL_H

#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <tuple>
#include "GameObject.h"


class Level {
    public: 
        Level(int t_size); 
        void CreateLevel(int width, int height);
        void UpdateLevel();
        void AddGameObject(int row, int col, int t_size, std::shared_ptr<GameObject> obj);
        void removeGameObject();
        void updateGameObject();
        std::vector<std::vector<std::shared_ptr<GameObject>>> level;
        int tile_size; 

    private:
        int height;
        int width;

};

#endif // LEVEL_H