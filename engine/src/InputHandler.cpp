#include "InputHandler.h"
#include <iostream>

void InputHandler::RegisterPlayer(std::shared_ptr<Player> player) {
    this->player = player;
}

void InputHandler::RegisterPlayerEvent(KeyboardKey key, Player::Action action) {
    this->ActionPairs.insert(std::make_pair(key, action));
}   

void InputHandler::HandlePlayerEvents() {
    for (const auto& [key,value] : this->ActionPairs) {
        if (IsKeyDown(key) && activeKeys.size() < 1) {
            if (this->ActionPairs[key] == Player::UP) {
                player->moveUp();
            } else if (this->ActionPairs[key] == Player::DOWN) {
                player->moveDown();
            } else if (this->ActionPairs[key] == Player::LEFT) {
                player->moveLeft();
            } else if (this->ActionPairs[key] == Player::RIGHT) {
                player->moveRight();
            }
        }
    }
}

