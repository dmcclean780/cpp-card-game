#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>

#include <string>
#include "../Settings.hpp"


class Screen {
    public:
        virtual ~Screen() = default;
        virtual void render(SDL_Renderer* renderer, Settings* settings) = 0;
        virtual void handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) = 0;
        virtual void update(SDL_Renderer* renderer, Settings *settings) = 0;
        virtual void onEnter(SDL_Window* window, Settings* settings) = 0;
};

#endif