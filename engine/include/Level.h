#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"


class Level {
    public: 
        
        void CreateLevel(int width, int height);

        void UpdateLevel();
        void addGameObject();
        void removeGameObject();
        void updateGameObject();
        std::vector<std::vector<std::shared_ptr<GameObject>>> level;

    private:
        int height;
        int width;

};