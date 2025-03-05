#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Player.h"
#include "raylib.h"
#include "Collider.h"
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <set>

class InputHandler {
private:
    std::shared_ptr<Collider> c;
public:
    InputHandler(std::shared_ptr<Collider>& collider); 
    void RegisterPlayer(std::shared_ptr<Player> player);
    void RegisterPlayerEvent(KeyboardKey key, Player::Action action);
    void HandlePlayerEvents();
    void CheckActiveKeys();

    std::shared_ptr<Player> player; 
    std::map<KeyboardKey, Player::Action> ActionPairs;
    std::set<int> activeKeys; 

};

#endif 
