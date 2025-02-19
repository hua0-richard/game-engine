#include "InputHandler.h"
#include <iostream>

void InputHandler::RegisterPlayerEvent(KeyboardKey KEY, const std::function<void()>& action) {
    if (IsKeyDown(KEY)) {
        action();
    }
}