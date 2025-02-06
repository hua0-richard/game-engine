#include <iostream>
#include <raylib.h>
using namespace std;

int main() {
    InitWindow(800, 800, "Game");
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(SKYBLUE);

        EndDrawing();
    }
    return 0;
}