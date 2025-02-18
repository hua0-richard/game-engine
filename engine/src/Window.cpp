#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string>
#include "Window.h"

Window::Window() {
}

Window::~Window(){}

void Window::Clear() {
    ClearBackground(BLACK);
}

void Window::Input() {
    
}

void Window::Draw() {
    // Some fixed width for each tile in level
    // Will draw all objects on screen 'in scope'
}

void Window::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing(); 
        // this->clear();
        // this->input();
        // this->update();
        // this->objects();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
}