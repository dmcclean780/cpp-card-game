#include "cpp-card-game/game-components/TurnCounter.hpp"
#include <iostream>

TurnCounter::TurnCounter( TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
    : color(color), font(font) {
    turnCounter = 0;
    updateTexture(renderer);
    
}

TurnCounter::~TurnCounter() {
    if (texture) SDL_DestroyTexture(texture);
}

void TurnCounter::updateTexture(SDL_Renderer* renderer) {
    if (texture) SDL_DestroyTexture(texture);

    int renderedTurns = (turnCounter == 0 || turnCounter == 1) ? 1 : turnCounter-1;
    std::string label = "Turn: " + std::to_string(renderedTurns);
    SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), color);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void TurnCounter::render(SDL_Renderer* renderer, Settings* settings) {

    // Draw background
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
   
    int xPosition = settings->screenWidth/4 * 3;
    int yPosition = settings->screenHeight / 8;
    rect = { xPosition, yPosition, width, height };
    // Draw text
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
