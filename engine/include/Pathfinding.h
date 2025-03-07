#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "Level.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include <memory>
#include <utility>
#include <map>

// Direction enum for tracking enemy movement
enum Direction {
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Heuristic types for A* pathfinding
enum HeuristicType {
    MANHATTAN,    
    EUCLIDEAN,    
    DIAGONAL,     
    NONE_HEURISTIC // No heuristic
};

class PathFinding {

    public: 
        std::shared_ptr<Level> level;
        std::vector<std::shared_ptr<Enemy>> enemies; 
        std::shared_ptr<Player> player;
        int frameCounter;
        
        std::map<std::shared_ptr<Enemy>, std::vector<std::pair<int, int>>> currentPaths;
        std::map<std::shared_ptr<Enemy>, size_t> pathIndices;
        std::map<std::shared_ptr<Enemy>, Direction> lastDirection;
        std::map<std::shared_ptr<Enemy>, int> directionChangeDelay;
        const int DIRECTION_CHANGE_DELAY = 0; 
        std::map<std::shared_ptr<Enemy>, bool> isFleeing;
        std::map<std::shared_ptr<Enemy>, Vector2> fleeTargets;
        std::map<std::shared_ptr<Enemy>, HeuristicType> enemyHeuristics;
        std::map<std::shared_ptr<Enemy>, float> enemySpeeds;
        std::map<std::shared_ptr<Enemy>, float> movementProgress;
        std::map<std::shared_ptr<Enemy>, int> enemyFrameCounters;
        const float DEFAULT_ENEMY_SPEED = 1.0f;

        PathFinding(std::shared_ptr<Level>& level);
        
        void RegisterPlayer(std::shared_ptr<Player> t_player);
        
        int heuristic(int x1, int y1, int x2, int y2, HeuristicType type = MANHATTAN);
        std::vector<std::pair<int, int>> findPath(int startX, int startY, int goalX, int goalY, HeuristicType heuristicType = MANHATTAN);
        void moveEnemyAlongPath(std::shared_ptr<Enemy>& enemy, const std::vector<std::pair<int, int>>& path);
        
        void continueExistingPath(std::shared_ptr<Enemy>& enemy);
        
        Direction getDirection(int currentX, int currentY, int nextX, int nextY);
        
        bool hasReachedTarget(std::shared_ptr<Enemy>& enemy, Vector2 target, float threshold = 1.0f);

        std::vector<std::vector<int>> Convert(std::shared_ptr<Level>& level);
        virtual void EnemyChase(HeuristicType heuristicType = MANHATTAN); 
        virtual void EnemyFlee(std::shared_ptr<Enemy>& enemy, Vector2 targetLocation, HeuristicType heuristicType = MANHATTAN);
        
        void SetFleeingState(std::shared_ptr<Enemy>& enemy, bool fleeing);
        
        void SetEnemyHeuristic(std::shared_ptr<Enemy>& enemy, HeuristicType type);

        void SetEnemySpeed(std::shared_ptr<Enemy>& enemy, float speed);

        void UpdateEnemyPosition(std::shared_ptr<Enemy>& enemy, int nextX, int nextY);

        void CalculatePathToPlayer(std::shared_ptr<Enemy>& enemy);
};


#endif // PATHFINDING_H
