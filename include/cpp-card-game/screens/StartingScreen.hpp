#ifndef STARTING_SCREEN_H
#define STARTING_SCREEN_H
#include <SDL.h>
#include <SDL_ttf.h>

#include "../Button.hpp"
#include "Screen.hpp"
#include "../ScreenManager.hpp"
#include "../TextBox.hpp"
#include "../Settings.hpp"


class StartingScreen : public Screen {
   public:
    StartingScreen(SDL_Renderer* renderer, ScreenManager* manager);
    void handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) override;
    void render(SDL_Renderer* renderer, Settings* settings) override;
    void update(SDL_Renderer* renderer, Settings *settings) override;
    void onEnter(SDL_Window* window, Settings* settings) override;

   private:
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<Button> settingsButton;
    std::unique_ptr<TextBox> titleText;
    ScreenManager* manager;
};

#endif