#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "Window.h"

Window::Window() {
}

Window::~Window(){}

void Window::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    while (!WindowShouldClose()) {
        BeginDrawing(); 
        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(BLUE);
        EndDrawing();
    }
    CloseWindow();
}