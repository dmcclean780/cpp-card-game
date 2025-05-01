#include "cpp-card-game/screens/SettingsScreen.hpp"

#include <iostream>

#include "cpp-card-game/Button.hpp"
#include "cpp-card-game/Colors.hpp"
#include "cpp-card-game/Fonts.hpp"
#include "cpp-card-game/screens/StartingScreen.hpp"

SettingsScreen::SettingsScreen(SDL_Renderer* renderer, ScreenManager* manager, Settings* settings)
    : manager(manager), settings(settings) {
    returnButton = std::make_unique<Button>(70, "Return", Fonts::Medium, Colors::WHITE, renderer);
    titleText = std::make_unique<TextBox>(100, "Settings", Fonts::Title, Colors::BLACK, renderer);
}

void SettingsScreen::handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (returnButton->isClicked(x, y)) {
           manager->requestScreenChange(std::make_unique<StartingScreen>(renderer, manager));
        }
    }
}

void SettingsScreen::update(SDL_Renderer* renderer, Settings *settings) {}

void SettingsScreen::render(SDL_Renderer* renderer, Settings* settings) {
    // Set background color
    SDL_SetRenderDrawColor(renderer, Colors::WHITE.r, Colors::WHITE.g, Colors::WHITE.b, Colors::WHITE.a);
    SDL_RenderClear(renderer);

    // Render buttons
    returnButton->render(renderer, settings);
    titleText->render(renderer, settings);
}

void SettingsScreen::onEnter(SDL_Window* window, Settings* settings) {
    // Any specific actions to take when entering the settings screen
    std::cout << "Settings screen entered" << std::endl;
}