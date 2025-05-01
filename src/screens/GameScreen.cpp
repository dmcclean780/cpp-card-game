#include "cpp-card-game/screens/GameScreen.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "cpp-card-game/Colors.hpp"
#include "cpp-card-game/game-components/Card.hpp"

GameScreen::GameScreen(SDL_Renderer *renderer, ScreenManager *manager, Settings *settings)
    : manager(manager) {
  deck = Deck(renderer);
  std::cout << "Deck created" << std::endl;
  deck.shuffleDeck();
  std::cout << "Deck shuffled" << std::endl;

  player.addCardToHand(deck.drawCard());
  player.addCardToHand(deck.drawCard());
  player.addCardToHand(deck.drawCard());
  player.addCardToHand(deck.drawCard());

  discardPile = DiscardPile(renderer);
}

void GameScreen::handleEvent(SDL_Event &event, SDL_Renderer *renderer, Settings *settings) {

  if (event.type == SDL_MOUSEBUTTONDOWN) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (turnsTaken == 0) {
      player.showClickedCards(mouseX, mouseY);
    }
    else if( turnsTaken == 1) {
      player.hideClickedCards(mouseX, mouseY);
    }
  }
}

void GameScreen::update(SDL_Renderer *renderer, Settings *settings) {
  player.updateCardRect(settings);
  if (turnsTaken == 0 && player.getVisableCards() == 2) {
    turnsTaken++;
  }
  else if (turnsTaken == 1 && player.getVisableCards() == 0) {
    turnsTaken++;
  }
}

void GameScreen::render(SDL_Renderer *renderer, Settings *settings) {
  SDL_SetRenderDrawColor(renderer, Colors::BLUE.r, Colors::BLUE.g, Colors::BLUE.b, Colors::BLUE.a);
  SDL_RenderClear(renderer);

  player.renderHand(renderer);
  deck.render(renderer, settings);
  discardPile.render(renderer, settings);
}

void GameScreen::onEnter(SDL_Window *window, Settings *settings) {
  // Any specific actions to take when entering the game screen
  std::cout << "Game screen entered" << std::endl;
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  // SDL_SetWindowResizable(window, SDL_TRUE);
  SDL_GetWindowSize(window, &settings->screenWidth, &settings->screenHeight);
}