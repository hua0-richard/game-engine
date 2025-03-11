#include "Character.h"
#include "Enemy.h"
#include <string>
class Ghost: public Enemy {
    public: 
        Texture2D ghostFleeSprite;
        Texture2D ghostDefaultSprite; 
        Texture2D eyeballSprite;
        bool texturesLoaded = false;
        bool didFlee = false; 
        bool didRetreat = false;
        float defaultSpeed = 0.5f;  

        Ghost();
        ~Ghost(); 
        
        void animate(float centerX, float centerY, float radius) override;
        void loadResource(char* resource) override;  
        void loadTextures(); 
        void Collision() override; 
};