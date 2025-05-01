#include "cpp-card-game/screens/LoadingScreen.hpp"
#include "cpp-card-game/Colors.hpp"
#include "cpp-card-game/screens/StartingScreen.hpp"

#include <iostream>

LoadingScreen::LoadingScreen(SDL_Renderer* renderer, ScreenManager* manager) 
    : manager(manager) {
    progress = 0;
}

void LoadingScreen::handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) {
}

void LoadingScreen::update(SDL_Renderer* renderer, Settings *settings) {
    // Simulate loading progress
    if (progress < 150) {
        progress++;
    } else {
        manager->requestScreenChange(std::make_unique<StartingScreen>(renderer, manager));
    }
}

void LoadingScreen::render(SDL_Renderer* renderer, Settings* settings) {
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r+progress, Colors::BLACK.g+progress, Colors::BLACK.b+progress, Colors::BLACK.a);
    SDL_RenderClear(renderer);
    SDL_Delay(10);
}

void LoadingScreen::onEnter(SDL_Window* window, Settings* settings) {
    // Any specific actions to take when entering the loading screen
    std::cout << "Loading screen entered" << std::endl;
}