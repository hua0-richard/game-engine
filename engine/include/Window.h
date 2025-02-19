#include "GameObject.h"
#ifndef WINDOW_H 
#define WINDOW_H

class Window {
public: 
    Window();
    ~Window();
    void Clear();
    void Input(); 
    void DrawLevel(std::vector<std::vector<std::shared_ptr<GameObject>>> &level);
    void Game(int width = 800, int height = 800, const char* title = "Game");
};


#endif