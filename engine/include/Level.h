#pragma once
#include <vector.h>
#include "GameObject.h"

class Level {
    public: 
        Level(); 
        ~Level();
        
        std::vector<std::vector<GameObject*>> CreateLevel(int width, int height) {
            return nullptr;
        }

        void UpdateLevel();
        void addGameObject();
        void removeGameObject();
        void updateGameObject();

    private:
        std::vector<GameObject*> GameObjectList;


};