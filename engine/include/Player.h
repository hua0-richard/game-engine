#include "GameObject.h"
#include "Raylib.h"
#include <memory>
#include <vector>
class Player : public GameObject {
    public: 
        enum Action  {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            ATTACK,
            DEFEND
        };

        Player();
        ~Player();    

        void moveUp();
        void moveDown(); 
        void moveLeft();
        void moveRight(); 
        void DrawSelf(int t_size) override;
        
}; 