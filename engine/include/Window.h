#ifndef WINDOW_H
#define WINDOW_H
#include "GameObject.h"
#include "Level.h"
#include "InputHandler.h"
#include "Collider.h"
#include <memory>
#include <vector>

class Window {
private:
    void ProcessInput(std::unique_ptr<InputHandler>& inputHandler);
    void Update(std::shared_ptr<Level>& level);
    void Render(std::shared_ptr<Level>& level);
    void Collision(std::shared_ptr<Collider>& collider);

public: 
    Window();
    ~Window();
    void Clear();
    void Input(); 
    void Update(std::vector<std::vector<std::shared_ptr<GameObject>>>& level, int t_size);
    void Game(
        std::unique_ptr<InputHandler>& inputHandler,
        std::shared_ptr<Level>& level,
        std::shared_ptr<Collider>& collider,
        int width = 800, 
        int height = 800, 
        const char* title = "Game", 
        int tile_size = 16
    );
};

#endif