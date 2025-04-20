#include "cpp-card-game/Button.hpp"
#include <iostream>

Button::Button(int x, int y, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
    : label(text) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
}

Button::~Button() {
    if (texture) SDL_DestroyTexture(texture);
}

void Button::render(SDL_Renderer* renderer) {
    // Draw background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect bg = { rect.x - 20, rect.y - 10, rect.w + 40, rect.h + 20 };
    SDL_RenderFillRect(renderer, &bg);

    // Draw text
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::isClicked(int mouseX, int mouseY) {
    return (mouseX > rect.x && mouseX < rect.x + rect.w &&
            mouseY > rect.y && mouseY < rect.y + rect.h);
}
