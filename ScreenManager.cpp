#include "ScreenManager.h"


void ScreenManager::pushScreen(Screen* screen) {
    _screens.push_back(screen);  // Add a screen to the stack
}

void ScreenManager::popScreen() {
    if (!_screens.empty()) {
        _screens.pop_back();
    }
}

void ScreenManager::showScreen() {
    if (_screens.empty()) {
        std::cout << "we have a rly big problem" << std::endl;
        return;
    }

    
    _screens.back()->render();
    
    
}

void ScreenManager::printScreens() {
    for (auto screen : _screens) {
        std::cout << screen << std::endl;
    }
}

Screen* ScreenManager::getCurrentScreen() {
    if (_screens.empty()) {
        std::cout << "we have a rly big problem" << std::endl;
        return nullptr;
    }
    return _screens.back();
}
