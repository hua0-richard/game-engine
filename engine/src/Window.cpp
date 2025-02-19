#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "GameObject.h"
#include "Window.h"
#include "Level.h"
#include "InputHandler.h"
#include <functional>

Window::Window() {
}

Window::~Window(){}

void Window::Clear() {
    ClearBackground(BLACK);
}

void Window::Input() {
    
}

void Window::DrawLevel(std::vector<std::vector<std::shared_ptr<GameObject>>> &level, int t_size) {
    // Some fixed width for each tile in level
    // Will draw all objects on screen 'in scope'
    for (auto& row: level) {
        for (auto& gameObject: row) {
            if (gameObject) {
                gameObject->DrawSelf(t_size);
            }
        } 
    }

}

void Window::Game(int width, int height, const char* title, int tile_size) {
    auto mainLevel = Level(tile_size);
    auto input = InputHandler();
    auto p = std::make_shared<Player>();
    InitWindow(mainLevel.tile_size * width, mainLevel.tile_size * height, title);
    SetTargetFPS(30);
    mainLevel.CreateLevel(28, 11);
    mainLevel.level[0][0] = p;

    while (!WindowShouldClose()) {
        Window::DrawLevel(mainLevel.level, mainLevel.tile_size);

        input.RegisterPlayerEvent(KEY_RIGHT, [&p]() { p->moveRight(); });
        input.RegisterPlayerEvent(KEY_LEFT, [&p]() { p->moveLeft(); });
        input.RegisterPlayerEvent(KEY_DOWN, [&p]() { p->moveUp(); });
        input.RegisterPlayerEvent(KEY_UP, [&p]() { p->moveDown(); });

        std::cout << p->m_position.x << std::endl;

        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
}