#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "GameObject.h"
#include "Window.h"
#include "Level.h"
#include "InputHandler.h"
#include "Character.h"
#include "Enemy.h"
#include "Collider.h"
#include <functional>

Window::Window() {
}

Window::~Window(){}

void Window::Clear() {
    ClearBackground(BLACK);
}

void Window::Input() {
    
}

void Window::Update(std::vector<std::vector<std::shared_ptr<GameObject>>>& level, int t_size) {
    for (auto& row: level) {
        for (auto& gameObject: row) {
            if (gameObject) {
                gameObject->DrawSelf(t_size);
            }
        } 
    }
}

void Window::ProcessInput(std::unique_ptr<InputHandler>& inputHandler) {
    inputHandler->HandlePlayerEvents();
}

void Window::Render(std::shared_ptr<Level>& level) {
    ClearBackground(BLACK);
    Update(level->level, level->tile_size);
    EndDrawing();
}

void Window::Collision(std::shared_ptr<Collider>& collider) {
    collider->DetectCollisions();
}

void Window::Game(
    std::unique_ptr<InputHandler>& inputHandler,
    std::shared_ptr<Level>& level,
    std::shared_ptr<Collider>& collider,
    int width,
    int height,
    const char* title,
    int tile_size
) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(level->tile_size * width, level->tile_size * height, title);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ProcessInput(inputHandler);
        Render(level);
        Update(level->level, tile_size);
        Collision(collider);
    }
    
    CloseWindow();
}