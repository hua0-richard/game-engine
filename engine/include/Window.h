#ifndef WINDOW_H 
#define WINDOW_H
#include "GameObject.h"
#include "Level.h"
#include <memory>
#include <vector>

class Window {
public: 
    Window();
    ~Window();
    void Clear();
    void Input(); 
    void DrawLevel(std::vector<std::vector<std::shared_ptr<GameObject>>> &level, int t_size);
    void Game(int width = 800, int height = 800, const char* title = "Game", int tile_size = 16);
};


#endif