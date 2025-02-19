#include "GameObject.h"
#include <memory>
#include <vector>
class Player : public GameObject {
    public: 
        Player();
        ~Player();    

        void moveForward();
        void moveBackward(); 
        void moveLeft();
        void moveRight(); 
        void DrawSelf() override;

    
    
}; 