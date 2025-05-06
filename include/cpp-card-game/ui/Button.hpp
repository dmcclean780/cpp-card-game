#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "../Settings.hpp"

class Button {
    public:
        Button(int y, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
        ~Button();
    
        void render(SDL_Renderer* renderer, Settings* settings);
        bool isClicked(int mouseX, int mouseY);
    
    private:
        SDL_Rect rect;
        SDL_Rect bgRect;
        SDL_Texture* texture;
        std::string label;
        int offset;
        SDL_Color color;
        TTF_Font* font;
    };

#endif