#include <iostream>
#include "Window.h"
using namespace std;

int main() {
    auto win = Window();
    // Original Game Resolution Scaled By 3
    win.Game(672, 864, "Pacman");
    return 0;
}