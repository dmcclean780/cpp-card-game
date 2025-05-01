#ifndef TEXT_BOX_H
#define TEXT_BOX_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Settings.hpp"

class TextBox {
    public:
        TextBox(int y, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
        ~TextBox();
    
        void render(SDL_Renderer* renderer, Settings* settings);
    
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        std::string label;
        int y;
        SDL_Color color;
        TTF_Font* font;
    };

#endif