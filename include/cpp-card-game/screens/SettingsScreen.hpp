#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H
#include <SDL.h>
#include <SDL_ttf.h>

#include "../ui/Button.hpp"
#include "Screen.hpp"
#include "../ScreenManager.hpp"
#include "../ui/TextBox.hpp"
#include "../Settings.hpp"

class SettingsScreen : public Screen {
   public:
    SettingsScreen(SDL_Renderer* renderer, ScreenManager* manager, Settings* settings);
    void handleEvent(SDL_Event& event, SDL_Renderer* rendere, Settings* settingsr) override;
    void render(SDL_Renderer* renderer, Settings* settings) override;
    void update(SDL_Renderer* renderer, Settings *settingsh) override;
    void onEnter(SDL_Window* window, Settings* settings) override;

   private:
    std::unique_ptr<Button> returnButton;
    std::unique_ptr<TextBox> titleText;
    ScreenManager* manager;
    Settings* settings;
};

#endif