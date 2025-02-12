#include <iostream> 
#include <raylib.h>
#include <cstddef>
#include <string.h>
#include "game.h"



Game::Game(int width, int height, std::string) {
    this->width = width;
    this->height = height;
    this->name = name; 
}

Game::~Game(){}

void Game::loop() {
    InitWindow(this->width, this->height, this->name.c_str());
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