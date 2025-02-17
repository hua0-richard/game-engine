#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string.h>
#include "Window.h"

Window::Window() {
}

Window::~Window(){}

void Window::Game() {
    InitWindow(800, 800, "game");
    while (!WindowShouldClose()) {
        BeginDrawing(); 
        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}