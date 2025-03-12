#include "Pathfinding.h"
#include "EnvironmentObject.h"
#include <queue>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Flee.h"
#include <random>

PathFinding::PathFinding(std::shared_ptr<Level>& level) {
    this->level = level;
    this->frameCounter = 0; 
}

void PathFinding::RegisterPlayer(std::shared_ptr<Player> t_player) {
    this->player = t_player;
}

void PathFinding::SetEnemyHeuristic(std::shared_ptr<Enemy> enemy, HeuristicType type) {
    enemyHeuristics[enemy] = type;
    // std::cout << "Set enemy heuristic to ";
    switch (type) {
        case MANHATTAN: std::cout << "Manhattan"; break;
        case EUCLIDEAN: std::cout << "Euclidean"; break;
        case DIAGONAL: std::cout << "Diagonal"; break;
        case NONE_HEURISTIC: std::cout << "None (Dijkstra)"; break;
    }
    std::cout << std::endl;
}

void PathFinding::SetEnemySpeed(std::shared_ptr<Enemy> enemy, float speed) {
    if (speed <= 0.0f) {
        speed = DEFAULT_ENEMY_SPEED;
    }
    
    enemySpeeds[enemy] = speed;
    enemyFrameCounters[enemy] = 0;
    movementProgress[enemy] = 0.0f;
    
    std::cout << "Set enemy speed to " << speed << " tiles per second" << std::endl;
}

std::vector<std::vector<int>> PathFinding::Convert(std::shared_ptr<Level>& level) {
    int height = level->level.size();
    if (height == 0) {
        std::cout << "Level has zero height!" << std::endl;
        return {};
    }
    
    int width = level->level[0].size();
    // std::cout << "Converting level grid: " << width << "x" << height << std::endl;
    
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto& obj = level->level[y][x];
            
            if (!obj) continue;
            
            auto environmentObj = std::dynamic_pointer_cast<EnvironmentObject>(obj);
            
            if (environmentObj) {
                grid[y][x] = 1; 
                // std::cout << "Environment obstacle at (" << x << "," << y << ")" << std::endl;
            } else {
                // std::cout << "Walkable space at (" << x << "," << y << ")" << std::endl;
            }
        }
    }
    
    return grid;
}

int PathFinding::heuristic(int x1, int y1, int x2, int y2, HeuristicType type) {
    switch (type) {
        case MANHATTAN:
            // Manhattan distance: |x1-x2| + |y1-y2|
            return std::abs(x1 - x2) + std::abs(y1 - y2);
            
        case EUCLIDEAN:
            // Euclidean distance: sqrt((x1-x2)² + (y1-y2)²)
            // Multiplied by 10 to keep it as integer and make it comparable to other heuristics
            {
                double dx = x1 - x2;
                double dy = y1 - y2;
                return static_cast<int>(10 * std::sqrt(dx * dx + dy * dy));
            }
            
        case DIAGONAL:
            // Diagonal/Chebyshev distance: max(|x1-x2|, |y1-y2|)
            return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
            
        case NONE_HEURISTIC:
            // No heuristic - turns A* into Dijkstra's algorithm
            return 0;
            
        default:
            // Default to Manhattan
            return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
}

// A* pathfinding algorithm
std::vector<std::pair<int, int>> PathFinding::findPath(int startX, int startY, int goalX, int goalY, HeuristicType heuristicType) {
    std::vector<std::vector<int>> grid = Convert(level);
    int height = grid.size();
    if (height == 0) return {};
    int width = grid[0].size();
    
    // Check if start or goal is out of bounds or on an obstacle
    if (startX < 0 || startX >= width || startY < 0 || startY >= height ||
        goalX < 0 || goalX >= width || goalY < 0 || goalY >= height ||
        grid[startY][startX] == 1 || grid[goalY][goalX] == 1) {
        return {}; // Return empty path if invalid
    }
    
    // Define possible movement directions (up, right, down, left)
    const std::vector<std::pair<int, int>> dirs = {
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}
    };
    
    // Priority queue for open set (f_score, (x, y))
    using Node = std::pair<int, std::pair<int, int>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    
    // Maps to store g_score, f_score and came_from
    std::map<std::pair<int, int>, int> gScore;
    std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    
    // Initialize start node
    std::pair<int, int> start = {startX, startY};
    std::pair<int, int> goal = {goalX, goalY};
    
    gScore[start] = 0;
    int fScore = heuristic(startX, startY, goalX, goalY, heuristicType);
    openSet.push({fScore, start});
    
    std::cout << "Using ";
    switch (heuristicType) {
        case MANHATTAN: std::cout << "Manhattan"; break;
        case EUCLIDEAN: std::cout << "Euclidean"; break;
        case DIAGONAL: std::cout << "Diagonal"; break;
        case NONE_HEURISTIC: std::cout << "None (Dijkstra)"; break;
    }
    std::cout << " heuristic for pathfinding" << std::endl;
    
    while (!openSet.empty()) {
        auto current = openSet.top().second;
        openSet.pop();
        
        // If we reached the goal, reconstruct the path
        if (current == goal) {
            std::vector<std::pair<int, int>> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        // Check all neighbors
        for (const auto& dir : dirs) {
            int newX = current.first + dir.first;
            int newY = current.second + dir.second;
            std::pair<int, int> neighbor = {newX, newY};
            
            // Check if neighbor is valid
            if (newX < 0 || newX >= width || newY < 0 || newY >= height || grid[newY][newX] == 1) {
                continue;
            }
            
            // Calculate tentative g score
            int tentative_gScore = gScore[current] + 1;
            
            // If this path is better than any previous one
            if (!gScore.count(neighbor) || tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                int f = tentative_gScore + heuristic(newX, newY, goalX, goalY, heuristicType);
                openSet.push({f, neighbor});
            }
        }
    }
    
    // No path found
    return {};
}

// Helper method to determine direction from current to next position
Direction PathFinding::getDirection(int currentX, int currentY, int nextX, int nextY) {
    if (nextX > currentX) return RIGHT;
    if (nextX < currentX) return LEFT;
    if (nextY > currentY) return DOWN;
    if (nextY < currentY) return UP;
    return NONE;
}

// Update enemy position based on speed and elapsed time
void PathFinding::UpdateEnemyPosition(std::shared_ptr<Enemy>& enemy, int nextX, int nextY) {
    // Ensure enemy has a speed set
    if (enemySpeeds.find(enemy) == enemySpeeds.end()) {
        enemySpeeds[enemy] = DEFAULT_ENEMY_SPEED;
        enemyFrameCounters[enemy] = 0;
        movementProgress[enemy] = 0.0f;
    }
    
    // Get current position
    int currentX = static_cast<int>(enemy->p_position.x);
    int currentY = static_cast<int>(enemy->p_position.y);
    
    // If already at the target position, nothing to do
    if (currentX == nextX && currentY == nextY) {
        return;
    }
    
    // Check if the enemy is already moving (p_position != m_position)
    if (static_cast<int>(enemy->p_position.x) != static_cast<int>(enemy->m_position.x) ||
        static_cast<int>(enemy->p_position.y) != static_cast<int>(enemy->m_position.y)) {
        // Enemy is still moving to its current target, don't change direction yet
        return;
    }
    
    // Calculate how many frames it should take to move one tile
    float framesPerTile = 60.0f / enemySpeeds[enemy]; // Assuming 60 FPS
    
    // Only set the target position, the Character's DrawSelf method will handle 
    // the smooth interpolation between p_position and m_position
    enemy->SeekTarget(nextX, nextY);
    
    // Reset counters for the next movement
    enemyFrameCounters[enemy] = 0;
    movementProgress[enemy] = 0.0f;
    
}

void PathFinding::moveEnemyAlongPath(std::shared_ptr<Enemy>& enemy, const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) return;
    
    currentPaths[enemy] = path;
    pathIndices[enemy] = 0;
    
    int currentX = static_cast<int>(enemy->p_position.x);
    int currentY = static_cast<int>(enemy->p_position.y);
    
    int nextX = path[0].first;
    int nextY = path[0].second;
    
    // Determine direction of movement
    Direction newDirection = getDirection(currentX, currentY, nextX, nextY);
    
    // Initialize direction if not set
    if (lastDirection.find(enemy) == lastDirection.end()) {
        lastDirection[enemy] = newDirection;
        directionChangeDelay[enemy] = 0;
    }
    // Check if direction has changed
    else if (lastDirection[enemy] != newDirection) {
        // Direction changed, set delay counter
        directionChangeDelay[enemy] = DIRECTION_CHANGE_DELAY;
        std::cout << "Direction changed! Adding delay." << std::endl;
        lastDirection[enemy] = newDirection;
        return;
    }
    
    UpdateEnemyPosition(enemy, nextX, nextY);
    
    if (newDirection == RIGHT) {
        // std::cout << "Moving right" << std::endl;
    } else if (newDirection == LEFT) {
        // std::cout << "Moving left" << std::endl;
    } else if (newDirection == DOWN) {
        // std::cout << "Moving down" << std::endl;
    } else if (newDirection == UP) {
        // std::cout << "Moving up" << std::endl;
    }
}

bool PathFinding::hasReachedTarget(std::shared_ptr<Enemy>& enemy, Vector2 target, float threshold) {
    if (!enemy) return false;
    
    float dx = enemy->p_position.x - target.x;
    float dy = enemy->p_position.y - target.y;
    float distanceSquared = dx * dx + dy * dy;
    
    // Using threshold squared to avoid square root calculation
    return distanceSquared <= (threshold * threshold);
}

void PathFinding::EnemyChase(HeuristicType heuristicType) {
    if (!player) {
        std::cout << "Player not registered with pathfinding system!" << std::endl;
        return;
    }
    
    if (enemies.empty()) {
        std::cout << "No enemies registered with pathfinding system!" << std::endl;
        return;
    }
    
    // Increment frame counter
    frameCounter++;
    
    // For each enemy, try to continue along existing path every frame
    for (auto& enemy : enemies) {
        if (!enemy) continue;
        
        // Initialize enemy heuristic if not set
        if (enemyHeuristics.find(enemy) == enemyHeuristics.end()) {
            enemyHeuristics[enemy] = heuristicType;
        }
        
        // Check if the enemy has reached its current target position
        int enemyX = static_cast<int>(enemy->p_position.x);
        int enemyY = static_cast<int>(enemy->p_position.y);
        int targetX = static_cast<int>(enemy->m_position.x);
        int targetY = static_cast<int>(enemy->m_position.y);
        
        bool needsNewPath = false;
        
        // If enemy has reached the current target
        if (enemyX == targetX && enemyY == targetY) {
            // Check if we've reached the end of the path
            if (currentPaths.find(enemy) == currentPaths.end() || 
                currentPaths[enemy].empty() ||
                pathIndices[enemy] >= currentPaths[enemy].size()) {
                // We need a new path
                needsNewPath = true;
                std::cout << "Enemy reached end of path, calculating new path" << std::endl;
        } else {
                // Continue along the existing path
                continueExistingPath(enemy);
            }
        }
        
        // Calculate a new path immediately if needed or wait for the normal interval
        if (needsNewPath || frameCounter % 180 == 0) {
            CalculatePathToPlayer(enemy);
        }
    }
    
    // Reset frame counter if it gets too large to prevent potential overflow
    if (frameCounter >= 6000) {
        frameCounter = 0;
    }
}

// Helper method to calculate path to player for a specific enemy
void PathFinding::CalculatePathToPlayer(std::shared_ptr<Enemy>& enemy) {
    if (!enemy || !player) return;
    
    // Get current positions
    int enemyX = static_cast<int>(enemy->p_position.x);
    int enemyY = static_cast<int>(enemy->p_position.y);
    int playerX = static_cast<int>(player->p_position.x);
    int playerY = static_cast<int>(player->p_position.y);

    if (enemy->flee) {  
        playerX = 1;
        playerY = 1; 
    }
    
    if (enemy->retreat) {
        playerX = enemy->spawn.x;
        playerY = enemy->spawn.y;
    }
    
    std::cout << "Enemy at (" << enemyX << "," << enemyY << "), Player at (" << playerX << "," << playerY << ")" << std::endl;
    
    // Make sure the positions are valid
    if (enemyX < 0 || enemyY < 0 || playerX < 0 || playerY < 0) {
        std::cout << "Invalid positions detected!" << std::endl;
        return;
    }
    
    // Use the enemy's configured heuristic
    HeuristicType currentHeuristic = enemyHeuristics[enemy];
    
    // Find path to player
    std::vector<std::pair<int, int>> path = findPath(enemyX, enemyY, playerX, playerY, currentHeuristic);
    
    if (path.empty()) {
        // Try a straight line if A* fails
        // if (enemyX < playerX) enemy->SeekTarget(enemyX + 1, enemyY);
        // else if (enemyX > playerX) enemy->SeekTarget(enemyX - 1, enemyY);
        // else if (enemyY < playerY) enemy->SeekTarget(enemyX, enemyY + 1);
        // else if (enemyY > playerY) enemy->SeekTarget(enemyX, enemyY - 1);
    } else {
        moveEnemyAlongPath(enemy, path);
    }
}

void PathFinding::EnemyFlee(std::shared_ptr<Enemy>& enemy, Vector2 targetLocation, HeuristicType heuristicType) {
    if (!enemy) {
        std::cout << "Null enemy in EnemyFlee!" << std::endl;
        return;
    }
    
    // Set the enemy's state to fleeing and store the target
    SetFleeingState(enemy, true);
    fleeTargets[enemy] = targetLocation;
    
    // Set heuristic for this enemy if not already set
    if (enemyHeuristics.find(enemy) == enemyHeuristics.end()) {
        enemyHeuristics[enemy] = heuristicType;
    }
    
    // Get current enemy position
    int enemyX = static_cast<int>(enemy->p_position.x);
    int enemyY = static_cast<int>(enemy->p_position.y);
    
    // Get target position
    int targetX = static_cast<int>(targetLocation.x);
    int targetY = static_cast<int>(targetLocation.y);
    
    std::cout << "Enemy fleeing from (" << enemyX << "," << enemyY << ") to target (" 
              << targetX << "," << targetY << ") using ";
    
    switch (enemyHeuristics[enemy]) {
        case MANHATTAN: std::cout << "Manhattan"; break;
        case EUCLIDEAN: std::cout << "Euclidean"; break;
        case DIAGONAL: std::cout << "Diagonal"; break;
        case NONE_HEURISTIC: std::cout << "None (Dijkstra)"; break;
    }
    std::cout << " heuristic" << std::endl;
    
    // Make sure the positions are valid
    if (enemyX < 0 || enemyY < 0 || targetX < 0 || targetY < 0) {
        std::cout << "Invalid positions detected in EnemyFlee!" << std::endl;
        return;
    }
    
    // Find path to the target location using A*
    std::vector<std::pair<int, int>> path = findPath(enemyX, enemyY, targetX, targetY, enemyHeuristics[enemy]);
    
    if (path.empty()) {
        std::cout << "No valid flee path found!" << std::endl;
        
        // Try a straight line if A* fails
        if (enemyX < targetX) enemy->SeekTarget(enemyX + 1, enemyY);
        else if (enemyX > targetX) enemy->SeekTarget(enemyX - 1, enemyY);
        else if (enemyY < targetY) enemy->SeekTarget(enemyX, enemyY + 1);
        else if (enemyY > targetY) enemy->SeekTarget(enemyX, enemyY - 1);
    } else {
        std::cout << "Flee path found with " << path.size() << " steps" << std::endl;
        moveEnemyAlongPath(enemy, path);
    }
}

void PathFinding::SetFleeingState(std::shared_ptr<Enemy>& enemy, bool fleeing) {
    isFleeing[enemy] = fleeing;
}

// Continue moving along the existing path
void PathFinding::continueExistingPath(std::shared_ptr<Enemy>& enemy) {
    // Check if we have a path for this enemy
    if (currentPaths.find(enemy) == currentPaths.end() || 
        currentPaths[enemy].empty() ||
        pathIndices[enemy] >= currentPaths[enemy].size()) {
        return;
    }
    
    // Check if the enemy is in a direction change delay
    if (directionChangeDelay.find(enemy) != directionChangeDelay.end() && 
        directionChangeDelay[enemy] > 0) {
        // Reduce the delay counter
        directionChangeDelay[enemy]--;
        std::cout << "Waiting for direction change: " << directionChangeDelay[enemy] << " frames left" << std::endl;
        return; // Don't move during delay
    }
    
    // Check if the enemy is still moving to its current target
    if (static_cast<int>(enemy->p_position.x) != static_cast<int>(enemy->m_position.x) ||
        static_cast<int>(enemy->p_position.y) != static_cast<int>(enemy->m_position.y)) {
        // Enemy is still moving, don't update target yet
        return;
    }
    
    // Get current position and next position in path
    int currentX = static_cast<int>(enemy->p_position.x);
    int currentY = static_cast<int>(enemy->p_position.y);
    
    // Get the next step in the path
    size_t currentIndex = pathIndices[enemy];
    int nextX = currentPaths[enemy][currentIndex].first;
    int nextY = currentPaths[enemy][currentIndex].second;
    
    // Determine direction of movement
    Direction newDirection = getDirection(currentX, currentY, nextX, nextY);
    
    // Check if direction has changed
    if (lastDirection.find(enemy) != lastDirection.end() && 
        lastDirection[enemy] != newDirection && 
        newDirection != NONE) {
        // Direction changed, set delay counter
        directionChangeDelay[enemy] = DIRECTION_CHANGE_DELAY;
        std::cout << "Direction changed during path! Adding delay." << std::endl;
        lastDirection[enemy] = newDirection;
        return; // Don't move yet, wait for delay
    }
    
    // Update the last direction
    if (newDirection != NONE) {
        lastDirection[enemy] = newDirection;
    }
    
    // std::cout << "Following path: moving enemy from (" << currentX << "," << currentY 
    //           << ") to (" << nextX << "," << nextY << ") [Step " 
    //           << currentIndex + 1 << "/" << currentPaths[enemy].size() << "]" << std::endl;
    
    // Update enemy position based on its speed
    UpdateEnemyPosition(enemy, nextX, nextY);
    
    // Only increment the path index if we've set a new target position
    pathIndices[enemy]++;
}
