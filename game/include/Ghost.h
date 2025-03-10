#include "Character.h"
#include "Enemy.h"
#include <string>
class Ghost: public Enemy {
    public: 
        Texture2D ghostFleeSprite;
        Texture2D ghostDefaultSprite; 
        bool flee = false;
        bool texturesLoaded = false;
        
        Ghost(); // Add constructor for proper initialization
        ~Ghost(); // Add destructor to unload textures
        
        void animate(float centerX, float centerY, float radius) override;
        void loadResource(char* resource) override;  
        void loadTextures(); // New method to load textures on demand
};