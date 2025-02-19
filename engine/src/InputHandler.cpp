#include "InputHandler.h"
#include <iostream>



void InputHandler::RegisterPlayerEvent(KeyboardKey KEY, const std::function<void()>& action) {
    if (IsKeyDown(KEY)) {
        action();
    }
}

void InputHandler::HandlePlayerEvents() {
    // iterate over all possible player actions
    // handle their associated events
}