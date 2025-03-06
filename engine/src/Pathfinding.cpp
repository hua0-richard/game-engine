#include "Pathfinding.h"

PathFinding::PathFinding(std::shared_ptr<Level>& level) {
    this->level = level;
}

void PathFinding::EnemyChase() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->m_position.x < 15 ) {
            enemies[i]->moveRight();
        } else {
            enemies[i]->moveLeft();
        }
    }
}

void PathFinding::EnemyFlee() {}
