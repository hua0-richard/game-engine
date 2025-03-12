#include "Flee.h"
#include <iostream>

bool FLEE = false;
int FLEE_DURATION = 600;
int FLEE_TIMER = 0;

void StartFleeTimer(int duration) {
    FLEE_DURATION = duration;
    FLEE_TIMER = duration;
    FLEE = true;
    std::cout << "FLEE mode activated for " << duration << " frames!" << std::endl;
}

void UpdateFleeTimer() {
    if (FLEE && FLEE_TIMER > 0) {
        FLEE_TIMER--;
        
        // Optional: Flash warning when timer is running low
        if (FLEE_TIMER < 90 && FLEE_TIMER % 15 == 0) {
            std::cout << "FLEE mode ending soon: " << FLEE_TIMER / 30 << " seconds left!" << std::endl;
        }
        
        // When timer reaches 0, deactivate FLEE mode
        if (FLEE_TIMER <= 0) {
            FLEE = false;
            std::cout << "FLEE mode deactivated!" << std::endl;
        }
    }
} 