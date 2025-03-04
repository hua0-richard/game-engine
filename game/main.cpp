#include <iostream>
#include "Window.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "EnvironmentObject.h"
using namespace std;

int main() {
    const int TILE_SIZE = 32; 
    // Create Level Player Enemy
    std::unique_ptr<Level> l = std::make_unique<Level>(TILE_SIZE);
    std::unique_ptr<InputHandler> input = std::make_unique<InputHandler>();
    std::shared_ptr<Player> player = std::make_shared<Player>();
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
    std::shared_ptr<EnvironmentObject> wall = std::make_shared<EnvironmentObject>();
    std::shared_ptr<EnvironmentObject> wall2 = std::make_shared<EnvironmentObject>();

    // Add To Level
    l->CreateLevel(20, 20);
    l->AddGameObject(3,3,TILE_SIZE, enemy);
    l->AddGameObject(6,6,TILE_SIZE, player);
    // l->AddGameObject(1,1,TILE_SIZE, wall);
    // l->AddGameObject(1,2,TILE_SIZE, wall);
    // l->AddGameObject(10,10,TILE_SIZE, wall2);


    // Register Player Actions
    input->RegisterPlayer(player);
    input->RegisterPlayerEvent(KEY_RIGHT, Player::RIGHT);
    input->RegisterPlayerEvent(KEY_LEFT, Player::LEFT);
    input->RegisterPlayerEvent(KEY_DOWN, Player::DOWN);
    input->RegisterPlayerEvent(KEY_UP, Player::UP);

    // Create Window 
    std::unique_ptr<Window> window = std::make_unique<Window>();

    // Original Game Resolution Scaled By 3
    window->Game(input, l, 20, 20, "Pacman", TILE_SIZE);
}