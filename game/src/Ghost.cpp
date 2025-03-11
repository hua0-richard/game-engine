#include "Ghost.h"
#include "GhostFleeMode.h"

Ghost::Ghost() {
    // Initialize default values in the constructor
    texturesLoaded = false;
}

Ghost::~Ghost() {
    // Clean up textures when the Ghost is destroyed
    if (texturesLoaded) {
        UnloadTexture(ghostFleeSprite);
        UnloadTexture(ghostDefaultSprite);
    }
}

void Ghost::loadTextures() {
    if (!texturesLoaded) {
        ghostDefaultSprite = LoadTexture(this->resource);
        ghostFleeSprite = LoadTexture("../assets/flee.png");
        eyeballSprite = LoadTexture("../assets/eyeball.png");
        
        if (ghostFleeSprite.id == 0) {
            std::cout << "Failed to load flee texture, using fallback" << std::endl;
        }
        
        if (resource != nullptr) {
            ghostDefaultSprite = LoadTexture(resource);
            if (ghostDefaultSprite.id == 0) {
                std::cout << "Failed to load default ghost texture, using fallback" << std::endl;
            }
        }
        texturesLoaded = true;
    }
}

void Ghost::animate(float centerX, float centerY, float radius) {
    loadTextures();

    if (this->flee == false && FLEE == true && this->didFlee == false) {
        this->flee = true; 
        this->didFlee = true; 
    }
    if (FLEE == false) {
        this->flee = false; 
        this->didFlee = false; 
        this->didRetreat = false;
    }

    if (m_position.x == this->spawn.x && m_position.y == this->spawn.y) {
        std::cout << "false" << std::endl;
        this->retreat = false;
        this->SetMoveSpeed(this->defaultSpeed);
    }

    if (this->retreat == true) {
        DrawTexture(eyeballSprite, centerX - radius, centerY - radius, WHITE);
        return;
    }
        
    if (!texturesLoaded || (ghostDefaultSprite.id == 0 && ghostFleeSprite.id == 0)) {
        DrawCircle(centerX, centerY, radius, RED);
    } else {
        if (!FLEE) {
            DrawTexture(ghostDefaultSprite, centerX - radius, centerY - radius, WHITE);
        } else if (FLEE && this->flee == false) {
            DrawTexture(ghostDefaultSprite, centerX - radius, centerY - radius, WHITE);
        }
        else if (FLEE && this->flee == true) {
            DrawTexture(ghostFleeSprite, centerX - radius, centerY - radius, WHITE);
        } else {
            DrawTexture(ghostDefaultSprite, centerX - radius, centerY - radius, WHITE);
        }
    }
}

void Ghost::loadResource( char* resource) {
    texturesLoaded = false; 
    Character::loadResource(resource);
}

void Ghost::Collision() {
    if (FLEE) {
        std::cout << "FLEE" << std::endl; 
    } else {
        std::cout << "No FLEE" << std::endl; 
    }
}