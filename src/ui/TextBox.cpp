#include "cpp-card-game/ui/TextBox.hpp"
#include <iostream>

TextBox::TextBox(int y, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
    : label(text), y(y), color(color), font(font) {

    
}

TextBox::~TextBox() {
    if (texture) SDL_DestroyTexture(texture);
}

void TextBox::render(SDL_Renderer* renderer, Settings* settings) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), color);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    

    SDL_FreeSurface(surface);

    // Draw background
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    int centerX = (settings->screenWidth - width) / 2;
    rect = { centerX, y, width, height };
    // Draw text
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
