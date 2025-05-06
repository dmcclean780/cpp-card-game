#include "cpp-card-game/screens/StartingScreen.hpp"

#include <iostream>

#include "cpp-card-game/ui/Button.hpp"
#include "cpp-card-game/Colors.hpp"
#include "cpp-card-game/Fonts.hpp"
#include "cpp-card-game/screens/SettingsScreen.hpp"
#include "cpp-card-game/screens/GameScreen.hpp"

StartingScreen::StartingScreen(SDL_Renderer* renderer, ScreenManager* manager) 
    : manager(manager) {
    startButton = std::make_unique<Button>(0, "Start Game", Fonts::Medium, Colors::WHITE, renderer);
    settingsButton = std::make_unique<Button>(70, "Settings", Fonts::Medium, Colors::WHITE, renderer);
    exitButton = std::make_unique<Button>(140, "Exit", Fonts::Medium, Colors::WHITE, renderer);
    titleText = std::make_unique<TextBox>(100, "HELLO WORLD", Fonts::Title, Colors::BLACK, renderer);
}

void StartingScreen::handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (startButton->isClicked(x, y)) {
            manager->requestScreenChange(std::make_unique<GameScreen>(renderer, manager, settings));
        }
        if (settingsButton->isClicked(x, y)) {
            manager->requestScreenChange(std::make_unique<SettingsScreen>(renderer, manager, settings));

        }
        if (exitButton->isClicked(x, y)) {
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
        }
    }
}

void StartingScreen::update(SDL_Renderer* renderer, Settings *settings) {
}

void StartingScreen::render(SDL_Renderer* renderer, Settings* settings) {
    // Set background color
    SDL_SetRenderDrawColor(renderer, Colors::WHITE.r, Colors::WHITE.g, Colors::WHITE.b, Colors::WHITE.a);
    SDL_RenderClear(renderer);
    SDL_Delay(10);

    // Render buttons
    startButton->render(renderer, settings);
    exitButton->render(renderer, settings);
    settingsButton->render(renderer, settings);
    titleText->render(renderer, settings);
}

void StartingScreen::onEnter(SDL_Window* window, Settings* settings) {
    // Any specific actions to take when entering the starting screen
    std::cout << "Starting screen entered" << std::endl;
}