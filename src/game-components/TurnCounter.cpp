#include "cpp-card-game/game-components/TurnCounter.hpp"
#include <iostream>

#include "cpp-card-game/Colors.hpp"

TurnCounter::TurnCounter(TTF_Font *font, SDL_Color color, SDL_Renderer *renderer)
    : color(color), font(font) {
  turnCounter = 0;
  updateCounterTexture(renderer);
  createLabelTexture(renderer);
}

TurnCounter::~TurnCounter() {
  if (turnCountTexture)
    SDL_DestroyTexture(turnCountTexture);
  if (labelTexture)
    SDL_DestroyTexture(labelTexture);
}

void TurnCounter::updateCounterTexture(SDL_Renderer *renderer) {
  if (turnCountTexture)
    SDL_DestroyTexture(turnCountTexture);

  int renderedTurns = (turnCounter == 0 || turnCounter == 1) ? 1 : turnCounter - 1;
  std::string label = std::to_string(renderedTurns);
  SDL_Surface *surface = TTF_RenderText_Solid(font, label.c_str(), color);
  if (!surface) {
    std::cerr << "Text render error: " << TTF_GetError() << std::endl;
    return;
  }

  turnCountTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void TurnCounter::createLabelTexture(SDL_Renderer *renderer) {
  if (labelTexture)
    SDL_DestroyTexture(labelTexture);

  std::string label = "Turn";
  SDL_Surface *surface = TTF_RenderText_Solid(font, label.c_str(), color);
  if (!surface) {
    std::cerr << "Text render error: " << TTF_GetError() << std::endl;
    return;
  }

  labelTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void TurnCounter::render(SDL_Renderer *renderer, Settings *settings) {

  renderBackground(renderer, settings);
  renderLabel(renderer, settings);
  renderCounter(renderer, settings);
}

void TurnCounter::renderBackground(SDL_Renderer *renderer, Settings *settings) {
  int labelWidth, labelHeight;
  SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelWidth, &labelHeight);

  int countWidth, countHeight;
  SDL_QueryTexture(turnCountTexture, nullptr, nullptr, &countWidth, &countHeight);

  int width = settings->screenWidth / 8;
  int height = settings->screenHeight / 8;

  int xPosition = settings->screenWidth / 4 * 3;
  int yPosition = settings->screenHeight / 8;
  SDL_Rect rect = {xPosition, yPosition, width, height};
  SDL_SetRenderDrawColor(renderer, Colors::DARK_GRAY.r, Colors::DARK_GRAY.g, Colors::DARK_GRAY.b, Colors::DARK_GRAY.a);
  SDL_RenderFillRect(renderer, &rect);
}

void TurnCounter::renderLabel(SDL_Renderer *renderer, Settings *settings) {
  int labelWidth, labelHeight;
  SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelWidth, &labelHeight);

  int xPosition = settings->screenWidth / 4 * 3 + (settings->screenWidth / 8 / 2 - labelWidth / 2);
  int yPosition = settings->screenHeight / 8;
  SDL_Rect rect = {xPosition, yPosition, labelWidth, labelHeight};
  SDL_RenderCopy(renderer, labelTexture, NULL, &rect);
}

void TurnCounter::renderCounter(SDL_Renderer *renderer, Settings *settings) {
  int labelWidth, labelHeight;
  SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelWidth, &labelHeight);

  int width, height;
  SDL_QueryTexture(turnCountTexture, nullptr, nullptr, &width, &height);

  int xPosition = settings->screenWidth / 4 * 3 + settings->screenWidth / 16 - width / 2;
  int yPosition = settings->screenHeight / 8 + settings->screenHeight / 16 - height / 2;
  SDL_Rect rect = {xPosition, yPosition, width, height};
  SDL_RenderCopy(renderer, turnCountTexture, NULL, &rect);
}
