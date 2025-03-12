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
#include "Flee.h"
#include "Pause.h"
#include <functional>

Window::Window() {
}

Window::~Window(){}

void Window::Clear() {
    ClearBackground(BLACK);
}

void Window::Input() {
    
}

// this fixes the draw order
std::vector<std::shared_ptr<GameObject>> Window::SortObjectDrawOrder(std::vector<std::vector<std::shared_ptr<GameObject>>>& level) {
    std::vector<std::shared_ptr<GameObject>> characters; 
    std::vector<std::shared_ptr<GameObject>> others; 
    std::vector<std::shared_ptr<GameObject>> ordered; 
    for (auto& row: level) {
        for (auto& gameObject: row){
            if (std::dynamic_pointer_cast<Character>(gameObject)) {
                characters.push_back(gameObject);
            } else {
                others.push_back(gameObject);
            }
        }
    }
    for (auto& o: others) {
        ordered.push_back(o);
    }
    for (auto& c: characters) {
        ordered.push_back(c);
    }
    return ordered; 
 } 

void Window::Update(std::vector<std::vector<std::shared_ptr<GameObject>>>& level, int t_size) {
    std::vector<std::shared_ptr<GameObject>> ordered = this->SortObjectDrawOrder(level);
    for (auto& gameObject: ordered) {
        if (gameObject) {
            gameObject->DrawSelf(t_size);
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
    pathfinding->EnemyChase(); 
}

void Window::UpdateFleeTimer() {
    ::UpdateFleeTimer();
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
    InitWindow(level->tile_size * width, level->tile_size * height + BottomBarHeight, title);
    SetTargetFPS(30);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            PAUSE = !PAUSE;
        }

        if (!PAUSE) {
            UpdateFleeTimer();             
            EnemyPathFinding(pathfinding); 
            ProcessInput(inputHandler);    
            Collision(collider);        
        } 
    
        // Update score before drawing
        UpdateScore();
        
        BeginDrawing();
        Render(level);
        if (PAUSE) {
            DrawText("PAUSED", (width * tile_size / 2) - (2 * tile_size), height * tile_size / 2, tile_size, WHITE);
        }
        DrawGUI(height, width, tile_size);
        EndDrawing();
    }
    
    CloseWindow();
}

void Window::DrawGUI(int height, int width, int tile_size) {
    std::string scoreStr = std::string(this->leftBottomText) + " " + std::to_string(this->playerScore);
    DrawText(scoreStr.c_str(), 0, tile_size * height, tile_size, WHITE);
    std::string livesStr = std::string(this->rightBottomText) + " " + std::to_string(this->playerLives);
    DrawText(livesStr.c_str(), (width * tile_size) - ((strlen(this->rightBottomText) * tile_size) / 3) - (tile_size * 2), tile_size * height, tile_size, WHITE);
}

void Window::AddBottomBar(int t_size, int height, const char* leftText, const char* rightText) {
    this->BottomBarHeight = height * t_size; 
    this->leftBottomText = leftText;
    this->rightBottomText = rightText; 
}

// Add method to register the player for score updates
void Window::RegisterPlayer(std::shared_ptr<Player> player) {
    this->player = player;
}

// Add method to update the player score
void Window::UpdateScore() {
    if (this->player) {
        this->playerScore = this->player->score;
        this->playerLives = this->player->lives; 
    }
}