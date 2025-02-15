#pragma once
#include "Screen.h"
#include <vector>
#include <iostream>

class ScreenManager {
    public: 
        static ScreenManager& getInstance() {
            static ScreenManager instance;
            return instance;
        }
        void pushScreen(Screen* screen);
        void popScreen();
        void showScreen();
        void printScreens();
        Screen* getCurrentScreen();
        
    private:
        std::vector<Screen *> _screens;
        ScreenManager() = default;

};
