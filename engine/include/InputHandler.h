#include "Player.h"
#include "raylib.h"
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <set>

class InputHandler {
    public:
    void RegisterPlayer(std::shared_ptr<Player> player);
    void RegisterPlayerEvent(KeyboardKey key, Player::Action action);
    void HandlePlayerEvents();
    void CheckActiveKeys();
    std::shared_ptr<Player> player; 
    std::map<KeyboardKey, Player::Action> ActionPairs;
    std::set<int> activeKeys; 
};
