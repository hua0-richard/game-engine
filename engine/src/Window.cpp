#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "GameObject.h"
#include "Window.h"
#include "Level.h"
#include "Player.h"

Window::Window() {
}

Window::~Window(){}

void Window::Clear() {
    ClearBackground(BLACK);
}

void Window::Input() {
    
}

void Window::DrawLevel(std::vector<std::vector<std::shared_ptr<GameObject>>> &level) {
    // Some fixed width for each tile in level
    // Will draw all objects on screen 'in scope'
    for (auto& row: level) {
        for (auto& gameObject: row) {
            if (gameObject) {
                gameObject->DrawSelf();
            }
        } 
    }

}

void Window::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    SetTargetFPS(30);
    auto mainLevel = Level();
    mainLevel.CreateLevel(28, 11);
    mainLevel.level[0][0] = std::make_shared<Player>();

    while (!WindowShouldClose()) {
        Window::DrawLevel(mainLevel.level);
        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
}