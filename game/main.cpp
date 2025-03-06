#include <iostream>
#include "Window.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "EnvironmentObject.h"
#include "Pacman.h"
#include "Wall.h"
#include "Collider.h"
#include "ConsumableObject.h"

using namespace std;

const int TILE_SIZE = 32; 

// 0 = empty space (path)
// 1 = wall
// 2 = pellet
// 3 = power pellet
// 4 = ghost spawn
// 5 = player spawn
const int PACMAN_LEVEL[20][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 1, 1, 4, 4, 1, 1, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 2, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
    {1, 3, 2, 1, 2, 2, 2, 2, 2, 5, 0, 2, 2, 2, 2, 2, 1, 2, 3, 1},
    {1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1},
    {1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void BuildGameLevel(std::shared_ptr<Level> &level, std::shared_ptr<Collider> &collider) {
    int height = level->level.size();
    int width = level->level[0].size();
    
    std::cout << "Building Pacman level: " << width << "x" << height << std::endl;
    
    // Player and enemy spawn positions
    Vector2 playerSpawn = {0, 0};
    std::vector<Vector2> ghostSpawns;
    
    // Create the level based on the PACMAN_LEVEL array
    for (int y = 0; y < height && y < 20; y++) {
        for (int x = 0; x < width && x < 20; x++) {
            switch (PACMAN_LEVEL[y][x]) {
                case 1: { // Wall
                    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
                    level->AddGameObject(y, x, TILE_SIZE, wall);
                    collider->RegisterRigidBody(wall);
                    break;
                }
                case 2: { // Regular pellet
                    std::shared_ptr<ConsumableObject> pellet = std::make_shared<ConsumableObject>();
                    level->AddGameObject(y, x, TILE_SIZE, pellet);
                    collider->RegisterTransparentBody(pellet);
                    break;
                }
                case 3: { // Power pellet (bigger pellet)
                    std::shared_ptr<ConsumableObject> powerPellet = std::make_shared<ConsumableObject>();
                    // Could customize power pellet here if there's a way to set size/appearance
                    level->AddGameObject(y, x, TILE_SIZE, powerPellet);
                    collider->RegisterTransparentBody(powerPellet);
                    break;
                }
                case 4: { // Ghost spawn location
                    ghostSpawns.push_back({static_cast<float>(x), static_cast<float>(y)});
                    break;
                }
                case 5: { // Player spawn location
                    playerSpawn = {static_cast<float>(x), static_cast<float>(y)};
                    break;
                }
                // Empty space (0) - do nothing
            }
        }
    }
    
    // Return the spawn locations if needed
    std::cout << "Player spawn at: (" << playerSpawn.x << "," << playerSpawn.y << ")" << std::endl;
    for (size_t i = 0; i < ghostSpawns.size(); i++) {
        std::cout << "Ghost " << i << " spawn at: (" << ghostSpawns[i].x << "," << ghostSpawns[i].y << ")" << std::endl;
    }
}

int main() {
    // Create Level Player Enemy
    std::shared_ptr<Collider> collider = std::make_shared<Collider>();
    std::shared_ptr<Level> l = std::make_shared<Level>(TILE_SIZE);
    std::shared_ptr<PathFinding> path = std::make_shared<PathFinding>(l);
    std::unique_ptr<InputHandler> input = std::make_unique<InputHandler>(collider);
    
    // Create Pacman and ghosts
    std::shared_ptr<Pacman> pacman = std::make_shared<Pacman>();
    
    // Define ghost characters with different colors/behaviors
    std::shared_ptr<Enemy> blinky = std::make_shared<Enemy>(); // Red ghost - direct chase
    std::shared_ptr<Enemy> pinky = std::make_shared<Enemy>();  // Pink ghost - anticipate player
    std::shared_ptr<Enemy> inky = std::make_shared<Enemy>();   // Blue ghost - flank player
    std::shared_ptr<Enemy> clyde = std::make_shared<Enemy>();  // Orange ghost - random movement

    l->CreateLevel(20, 20);
    
    BuildGameLevel(l, collider);
    
    Vector2 playerSpawn = {9, 16}; 
    std::vector<Vector2> ghostSpawns = {{9, 8}, {10, 8}}; // Default positions from level
    
    // Place Pacman at the spawn point
    l->AddGameObject(playerSpawn.y, playerSpawn.x, TILE_SIZE, pacman);
    collider->RegisterCharacterBody(pacman);
    
    // Place ghosts at their spawn points with different heuristics
    if (ghostSpawns.size() >= 1) {
        l->AddGameObject(ghostSpawns[0].y, ghostSpawns[0].x, TILE_SIZE, blinky);
        collider->RegisterCharacterBody(blinky);
        path->enemies.push_back(blinky);
        path->SetEnemyHeuristic(blinky, MANHATTAN); // Direct chase using Manhattan distance
        path->SetEnemySpeed(blinky, 4.5f);          // Fast speed (tiles per second)
    }
    
    if (ghostSpawns.size() >= 2) {
        l->AddGameObject(ghostSpawns[1].y, ghostSpawns[1].x, TILE_SIZE, pinky);
        collider->RegisterCharacterBody(pinky);
        path->enemies.push_back(pinky);
        path->SetEnemyHeuristic(pinky, EUCLIDEAN); // Uses Euclidean distance
        path->SetEnemySpeed(pinky, 4.0f);          // Medium-fast speed
    }
    
    // Place additional ghosts if we have more spawn points
    if (ghostSpawns.size() >= 3) {
        Vector2 inkySpawn = {ghostSpawns[0].x - 1, ghostSpawns[0].y};
        l->AddGameObject(inkySpawn.y, inkySpawn.x, TILE_SIZE, inky);
        collider->RegisterCharacterBody(inky);
        path->enemies.push_back(inky);
        path->SetEnemyHeuristic(inky, DIAGONAL); // Uses diagonal/Chebyshev distance
        path->SetEnemySpeed(inky, 3.5f);         // Medium speed
    }
    
    if (ghostSpawns.size() >= 4) {
        Vector2 clydeSpawn = {ghostSpawns[0].x + 1, ghostSpawns[0].y};
        l->AddGameObject(clydeSpawn.y, clydeSpawn.x, TILE_SIZE, clyde);
        collider->RegisterCharacterBody(clyde);
        path->enemies.push_back(clyde);
        path->SetEnemyHeuristic(clyde, NONE_HEURISTIC); // Uses Dijkstra's algorithm (no heuristic)
        path->SetEnemySpeed(clyde, 3.0f);               // Slow speed
    }
    
    // Register player with pathfinding so enemies can chase
    path->RegisterPlayer(pacman);
    
    // Register Player Actions
    input->RegisterPlayer(pacman);
    input->RegisterPlayerEvent(KEY_RIGHT, Player::RIGHT);
    input->RegisterPlayerEvent(KEY_LEFT, Player::LEFT);
    input->RegisterPlayerEvent(KEY_DOWN, Player::DOWN);
    input->RegisterPlayerEvent(KEY_UP, Player::UP);

    // Create Window 
    std::unique_ptr<Window> window = std::make_unique<Window>();

    window->Game(input, l, collider, path, 20, 20, "Pacman", TILE_SIZE);
}