#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "GameObject.h"
#include "Window.h"
#include "Level.h"
#include "InputHandler.h"
#include "Character.h"
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
    auto player = std::make_shared<Player>();
    auto input = InputHandler();
    InitWindow(mainLevel.tile_size * width, mainLevel.tile_size * height, title);
    SetTargetFPS(60);
    mainLevel.CreateLevel(28, 11);
    mainLevel.level[2][2] = player;

    input.RegisterPlayer(player);
    input.RegisterPlayerEvent(KEY_RIGHT, Character::RIGHT);
    input.RegisterPlayerEvent(KEY_LEFT, Character::LEFT);
    input.RegisterPlayerEvent(KEY_DOWN, Character::DOWN);
    input.RegisterPlayerEvent(KEY_UP, Character::UP);

    while (!WindowShouldClose()) {
        Window::DrawLevel(mainLevel.level, mainLevel.tile_size);
        input.HandlePlayerEvents();
        // add a function to inputhandler to handle all possible actions for the player and their associated key binds
        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
}