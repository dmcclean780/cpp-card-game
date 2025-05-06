#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H
#include <SDL.h>
#include <SDL_ttf.h>

#include "Screen.hpp"
#include "../ScreenManager.hpp"
#include "../Settings.hpp"
#include "cpp-card-game/game-components/Deck.hpp"
#include "cpp-card-game/game-components/Player.hpp"
#include "cpp-card-game/game-components/DiscardPile.hpp"
#include "cpp-card-game/game-components/TurnCounter.hpp"


class GameScreen : public Screen {
   public:
    GameScreen(SDL_Renderer* renderer, ScreenManager* manager, Settings* settings);
    void handleEvent(SDL_Event& event, SDL_Renderer* renderer, Settings* settings) override;
    void render(SDL_Renderer* renderer, Settings* settings) override;
    void update(SDL_Renderer* renderer, Settings *settings) override;
    void onEnter(SDL_Window* window, Settings* settings) override;

   private:
    ScreenManager* manager;
    Deck deck;
    Player player;
    DiscardPile discardPile;
    std::unique_ptr<TurnCounter> turnCounter;
};

#endif