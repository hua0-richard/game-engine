#ifndef WINDOW_H
#define WINDOW_H
#include "GameObject.h"
#include "Level.h"
#include "InputHandler.h"
#include "Collider.h"
#include "Pathfinding.h"
#include "Player.h"
#include <memory>
#include <vector>

class Window {
private:
    int BottomBarHeight = 0;
    int TopBarHeight = 0;
    const char* leftBottomText = ""; 
    const char* rightBottomText = "";
    int playerScore = 0;
    int playerLives = 0;
    std::shared_ptr<Player> player;
    void ProcessInput(std::unique_ptr<InputHandler>& inputHandler);
    void Update(std::shared_ptr<Level>& level);
    void Render(std::shared_ptr<Level>& level);
    void Collision(std::shared_ptr<Collider>& collider);
    void EnemyPathFinding(std::shared_ptr<PathFinding> pathfinding);
    void UpdateFleeTimer();
    void DrawGUI(int height, int width, int tile_size = 16); 
    std::vector<std::shared_ptr<GameObject>> SortObjectDrawOrder(std::vector<std::vector<std::shared_ptr<GameObject>>>& level); 
public: 
    Window();
    ~Window();
    void Clear();
    void Input(); 
    void Update(std::vector<std::vector<std::shared_ptr<GameObject>>>& level, int t_size);
    void Game(
        std::unique_ptr<InputHandler>& inputHandler,
        std::shared_ptr<Level>& level,
        std::shared_ptr<Collider>& collider,
        std::shared_ptr<PathFinding>& pathfinding,
        int width = 800, 
        int height = 800, 
        const char* title = "Game", 
        int tile_size = 16
    );
    void AddBottomBar(int t_size = 16, int height = 0, const char* leftText = "", const char* rightText = ""); 
    void RegisterPlayer(std::shared_ptr<Player> player);
    void UpdateScore();
};

#endif