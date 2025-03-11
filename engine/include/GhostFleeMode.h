// global.h
#ifndef GLOBAL_H
#define GLOBAL_H

extern bool FLEE; // Declaration
extern int FLEE_DURATION; // Duration of flee mode in frames
extern int FLEE_TIMER; // Current timer value

// Start the flee timer with the given duration
void StartFleeTimer(int duration = 300); // Default 10 seconds at 30 FPS

// Update the flee timer - should be called each frame
void UpdateFleeTimer();

#endif
