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
        // work on these methods
        void removeGameObject();
        void updateGameObject();
        void updateSelf(); 
        std::vector<std::vector<std::shared_ptr<GameObject>>> level;
        int tile_size; 

    private:
        int height;
        int width;
        std::vector<std::shared_ptr<Character>> moveable_objects; 

};

#endif // LEVEL_H