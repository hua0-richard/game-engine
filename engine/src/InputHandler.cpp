#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(std::shared_ptr<Collider>& collider) {
    this->c = collider; 
}

void InputHandler::RegisterPlayer(std::shared_ptr<Player> player) {
    this->player = player;
}

void InputHandler::RegisterPlayerEvent(KeyboardKey key, Player::Action action) {
    this->ActionPairs.insert(std::make_pair(key, action));
}   

void InputHandler::HandlePlayerEvents() {
    for (const auto& [key,value] : this->ActionPairs) {
        if (IsKeyDown(key) && activeKeys.size() < 1) {
            Vector2 tmp_pos = player->m_position;
            if (this->ActionPairs[key] == Player::UP) {
                tmp_pos.y -= 1; 
                if (c->CheckRigidBodyCollisionsPlayer(tmp_pos)) {return; }
                player->moveUp();
            } else if (this->ActionPairs[key] == Player::DOWN) {
                tmp_pos.y += 1; 
                if (c->CheckRigidBodyCollisionsPlayer(tmp_pos)) {return; }
                player->moveDown();
            } else if (this->ActionPairs[key] == Player::LEFT) {
                tmp_pos.x -= 1; 
                if (c->CheckRigidBodyCollisionsPlayer(tmp_pos)) {return; }
                player->moveLeft();
            } else if (this->ActionPairs[key] == Player::RIGHT) {
                tmp_pos.x += 1; 
                if (c->CheckRigidBodyCollisionsPlayer(tmp_pos)) {return; };
                player->moveRight();
            }
        }
    }
}

