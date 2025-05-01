// ScreenManager.h
#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include <memory>
#include "screens/Screen.hpp"

class ScreenManager {
public:
    void setScreen(std::unique_ptr<Screen> newScreen) {
        screen = std::move(newScreen);
    }

    void handleEvents(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) {
        if (screen) screen->handleEvent(event, renderer, settings);
    }

    void update(SDL_Renderer* renderer, Settings *settings) {
        if (screen) screen->update(renderer, settings);
    }

    void render(SDL_Renderer* renderer, Settings* settings) {
        if (screen) screen->render(renderer, settings);
    }

    void requestScreenChange(std::unique_ptr<Screen> newScreen) {
        pendingScreen = std::move(newScreen);
    }
    
    void applyPendingScreenChange(SDL_Window* window, Settings* settings) {
        if (pendingScreen) {
            screen = std::move(pendingScreen);
            screen->onEnter(window, settings);
        }
    }

private:
    std::unique_ptr<Screen> screen;
    std::unique_ptr<Screen> pendingScreen;
};

#endif