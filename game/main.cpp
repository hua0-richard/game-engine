#include <iostream>
#include "Window.h"
using namespace std;

int main() {
    auto win = Window();
    // Original Game Resolution Scaled By 3
    win.Game(28, 36, "Pacman", 24);
    return 0;
}