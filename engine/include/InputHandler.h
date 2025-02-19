#include "Player.h"
#include "raylib.h"
#include <string>
#include <iostream>

class InputHandler {
    public:
    void RegisterPlayerEvent(KeyboardKey KEY, const std::function<void()>& action); 
    void HandlePlayerEvents();
};