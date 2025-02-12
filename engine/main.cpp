#include <iostream>
#include "game.h"
using namespace std;

int main() {
    Game game(800, 600, "My Game");
    game.loop();
    return 0;
}