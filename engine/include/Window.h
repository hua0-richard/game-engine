#ifndef WINDOW_H 
#define WINDOW_H

class Window {
public: 
    Window();
    ~Window();
    void Game(int width = 800, int height = 800, const char* title = "Game");
};


#endif