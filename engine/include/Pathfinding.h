#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "Level.h"
#include "Enemy.h"

// Empty file for now
class PathFinding {

    public: 
        std::shared_ptr<Level> level;
        std::vector<std::shared_ptr<Enemy>> enemies; 

        PathFinding(std::shared_ptr<Level>& level);

        std::vector<std::vector<int>> Convert(std::shared_ptr<Level>& level);
        virtual void EnemyChase(); 
        virtual void EnemyFlee();
};


#endif // PATHFINDING_H
