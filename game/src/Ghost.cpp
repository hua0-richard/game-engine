#include "Ghost.h"

Ghost::Ghost() {
    // Initialize default values in the constructor
    flee = false;
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
        // Load textures safely with error checking
        ghostFleeSprite = LoadTexture("../assets/flee.png");
        
        // Check if the texture was loaded successfully
        // ImageReady returns true if the image is valid
        if (ghostFleeSprite.id == 0) {
            // Texture failed to load, use a fallback color
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
    // Make sure textures are loaded before trying to use them
    loadTextures();
    
    if (!texturesLoaded || (ghostDefaultSprite.id == 0 && ghostFleeSprite.id == 0)) {
        // Fallback to circle if textures couldn't be loaded
        Color ghostColor = flee ? BLUE : RED;
        DrawCircle(centerX, centerY, radius, ghostColor);
    } else {
        if (!flee && ghostDefaultSprite.id != 0) {
            DrawTexture(ghostDefaultSprite, centerX - radius, centerY - radius, WHITE);
        } else if (flee && ghostFleeSprite.id != 0) {
            DrawTexture(ghostFleeSprite, centerX - radius, centerY - radius, WHITE);
        } else {
            // Fallback if the specific texture isn't available
            Color ghostColor = flee ? BLUE : RED;
            DrawCircle(centerX, centerY, radius, ghostColor);
        }
    }
}

void Ghost::loadResource(char* resource) {
    this->resource = resource;
    // Don't load the texture here, wait until it's needed
    texturesLoaded = false; // Reset so textures will be reloaded
}