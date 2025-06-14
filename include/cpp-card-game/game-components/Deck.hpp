#ifndef DECK_H
#define DECK_H

#include <string>
#include <SDL.h>

#include "Card.hpp"
#include "../Settings.hpp"

class Deck {
    private:
        Card deck[52];
        int deckTop = 0; // Index of the top card in the deck
        std::shared_ptr<SDL_Texture> backTexture;
        void loadBackTexture(SDL_Renderer* renderer);
        void calculateDeckDimensions(Settings* settings, int& cardWidthScaled, int&cardHeightScaled) const;

        int getDeckXCoord(Settings* settings) const {
            return settings->screenWidth / 3;
        }
        int getDeckYCoord(Settings* settings) const {
            return settings->screenHeight / 3;
        }
        int getDeckWidth(Settings* settings) const {
            return settings->screenWidth / 4;
        }
        int getDeckHeight(Settings* settings) const {
            return settings->screenHeight / 3;
        }

    public:
        Deck(SDL_Renderer* renderer);
        Deck();
        void printDeck() const;
        void shuffleDeck();
        Card drawCard();
        bool isEmpty() const {
            return deckTop >= 52;
        }
        void render(SDL_Renderer* renderer, Settings* settings) const;
};

#endif