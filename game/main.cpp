#include <iostream>
#include "Window.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "EnvironmentObject.h"
#include "Pacman.h"
#include "Wall.h"
#include "Collider.h"
using namespace std;

const int TILE_SIZE = 32; 


void BuildGameLevel(std::shared_ptr<Level> &level, std::shared_ptr<Collider> &collider) {
    int width = level->level.size();
    int height = level->level[0].size(); 
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (j == 0 || i == 0 || i == width - 1 || j == height - 1) {
                std::shared_ptr<Wall> wall = std::make_shared<Wall>();
               level->AddGameObject(i, j, TILE_SIZE, wall);
               collider->RegisterRigidBody(wall);
            }
        }
    }
}

int main() {
    // Create Level Player Enemy
    std::shared_ptr<Collider> collider = std::make_shared<Collider>();
    std::shared_ptr<Level> l = std::make_shared<Level>(TILE_SIZE);
    std::unique_ptr<InputHandler> input = std::make_unique<InputHandler>(collider);
    std::shared_ptr<Wall> blob = std::make_shared<Wall>();
    std::shared_ptr<Wall> blob2 = std::make_shared<Wall>();
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
    std::shared_ptr<Pacman> pacman = std::make_shared<Pacman>();




    // Add To Level
    l->CreateLevel(20, 20);
    
    // Build the walls around the level
    BuildGameLevel(l, collider);
    
    l->AddGameObject(3,3,TILE_SIZE, enemy);
    l->AddGameObject(8,8,TILE_SIZE, pacman);

    l->AddGameObject(5,5,TILE_SIZE, blob);
    collider->RegisterRigidBody(blob);
    l->AddGameObject(6,6,TILE_SIZE, blob2);
    collider->RegisterRigidBody(blob2);

    // Register Player Actions
    input->RegisterPlayer(pacman);
    input->RegisterPlayerEvent(KEY_RIGHT, Player::RIGHT);
    input->RegisterPlayerEvent(KEY_LEFT, Player::LEFT);
    input->RegisterPlayerEvent(KEY_DOWN, Player::DOWN);
    input->RegisterPlayerEvent(KEY_UP, Player::UP);
    collider->RegisterCharacterBody(pacman);

    // Create Window 
    std::unique_ptr<Window> window = std::make_unique<Window>();

    window->Game(input, l, collider, 20, 20, "Pacman", TILE_SIZE);
}