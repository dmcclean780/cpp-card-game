#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H
#include <SDL.h>
#include <SDL_ttf.h>

#include "Screen.hpp"
#include "../ScreenManager.hpp"
#include "../Settings.hpp"


class LoadingScreen : public Screen {
   public:
    LoadingScreen(SDL_Renderer* renderer, ScreenManager* manager);
    void handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) override;
    void render(SDL_Renderer* renderer, Settings* settings) override;
    void update(SDL_Renderer* renderer, Settings *settings) override;
    void onEnter(SDL_Window* window, Settings* settings) override;

   private:
    int progress = 0;
    ScreenManager* manager;
};

#endif