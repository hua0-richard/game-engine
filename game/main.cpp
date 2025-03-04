#include <iostream>
#include "Window.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "EnvironmentObject.h"
#include "Pacman.h"
#include "Wall.h"
using namespace std;

const int TILE_SIZE = 16; 


void BuildGameLevel(std::shared_ptr<Level> &level) {
    int width = level->level.size();
    int height = level->level[0].size(); 
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (j == 0 || i == 0 || i == width - 1 || j == height - 1) {
               level->AddGameObject(i, j, TILE_SIZE, std::make_shared<Wall>());
            }
        }
    }
}

int main() {
    // Create Level Player Enemy
    std::shared_ptr<Level> l = std::make_shared<Level>(TILE_SIZE);
    std::unique_ptr<InputHandler> input = std::make_unique<InputHandler>();
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
    std::shared_ptr<EnvironmentObject> wall = std::make_shared<EnvironmentObject>();
    std::shared_ptr<EnvironmentObject> wall2 = std::make_shared<EnvironmentObject>();


    std::shared_ptr<Pacman> pacman = std::make_shared<Pacman>();
    // Add To Level
    l->CreateLevel(20, 20);
    
    // Build the walls around the level
    BuildGameLevel(l);
    
    l->AddGameObject(3,3,TILE_SIZE, enemy);
    l->AddGameObject(8,8,TILE_SIZE, pacman);
    // l->AddGameObject(1,1,TILE_SIZE, wall);
    // l->AddGameObject(1,2,TILE_SIZE, wall);
    // l->AddGameObject(10,10,TILE_SIZE, wall2);

    // Register Player Actions
    input->RegisterPlayer(pacman);
    input->RegisterPlayerEvent(KEY_RIGHT, Player::RIGHT);
    input->RegisterPlayerEvent(KEY_LEFT, Player::LEFT);
    input->RegisterPlayerEvent(KEY_DOWN, Player::DOWN);
    input->RegisterPlayerEvent(KEY_UP, Player::UP);

    // Create Window 
    std::unique_ptr<Window> window = std::make_unique<Window>();

    // Original Game Resolution Scaled By 3
    window->Game(input, l, 20, 20, "Pacman", TILE_SIZE);
}