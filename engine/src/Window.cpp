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
}

void Window::Collision(std::shared_ptr<Collider>& collider) {
    collider->DetectCollisions();
}

void Window::EnemyPathFinding(std::shared_ptr<PathFinding> pathfinding) {
    // This is called every frame, but A* algorithm runs only every 60 frames
    // (controlled by the frameCounter in the PathFinding class)
    pathfinding->EnemyChase(); 
}

void Window::Game(
    std::unique_ptr<InputHandler>& inputHandler,
    std::shared_ptr<Level>& level,
    std::shared_ptr<Collider>& collider,
    std::shared_ptr<PathFinding>& pathfinding,
    int width,
    int height,
    const char* title,
    int tile_size
) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(level->tile_size * width, level->tile_size * height, title);
    SetTargetFPS(60);
    
    // Print a message when the game starts
    std::cout << "Game loop starting - enemy should start chasing player" << std::endl;
    
    while (!WindowShouldClose()) {
        // Process game logic before rendering
        EnemyPathFinding(pathfinding);  // Update enemy pathfinding
        ProcessInput(inputHandler);     // Handle player input
        Collision(collider);            // Detect and resolve collisions
        
        // Begin rendering frame
        BeginDrawing();
        
        // Render the game world
        Render(level);
        
        // End rendering frame
        EndDrawing();
    }
    
    CloseWindow();
}