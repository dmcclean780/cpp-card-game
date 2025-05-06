#include "cpp-card-game/ui/Button.hpp"
#include <iostream>

Button::Button(int offset, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
    : label(text), offset(offset), color(color), font(font) {

        SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), color);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    

    SDL_FreeSurface(surface);
    
}

Button::~Button() {
    if (texture) SDL_DestroyTexture(texture);
}

void Button::render(SDL_Renderer* renderer, Settings* settings) {

    

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    int centerX = (settings->screenWidth - width) / 2;
    int centerY = (settings->screenHeight - height) / 3 + offset;
    rect = { centerX, centerY, width, height };
    bgRect = { settings->screenWidth/3, rect.y-10, settings->screenWidth/3, rect.h+20 };

    // Draw background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &bgRect);

    // Draw text
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::isClicked(int mouseX, int mouseY) {
    return (mouseX > bgRect.x && mouseX < bgRect.x + bgRect.w &&
            mouseY > bgRect.y && mouseY < bgRect.y + bgRect.h);
}
