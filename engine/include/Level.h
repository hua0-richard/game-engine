#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

class Level {
    public: 
        Level(); 
        ~Level();
        
        void CreateLevel(int width, int height);

        void UpdateLevel();
        void addGameObject();
        void removeGameObject();
        void updateGameObject();

    private:
        int height;
        int width;
        std::vector<std::shared_ptr<GameObject>> GameObjectList;
        std::vector<std::vector<std::shared_ptr<GameObject>>> level;

};