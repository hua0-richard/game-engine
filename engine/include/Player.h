#include "GameObject.h"
#include <memory>
#include <vector>
class Player : public GameObject {
    public: 
        Player();
        ~Player();    

        void moveUp();
        void moveDown(); 
        void moveLeft();
        void moveRight(); 
        void DrawSelf(int t_size) override;
        
        
}; 