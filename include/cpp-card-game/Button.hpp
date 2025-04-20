#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Button {
    public:
        Button(int x, int y, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
        ~Button();
    
        void render(SDL_Renderer* renderer);
        bool isClicked(int mouseX, int mouseY);
    
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        std::string label;
    };

#endif