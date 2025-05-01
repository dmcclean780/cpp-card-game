#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <string>
#include <SDL.h>

#include "Card.hpp"
#include "../Settings.hpp"

class DiscardPile {
    private:
        Card discardPile[52];
        int discardTop = 52; // Index of the top card in the deck
        std::shared_ptr<SDL_Texture> backTexture;
        void loadBackTexture(SDL_Renderer* renderer);
        void calculateCardDimensions(Settings* settings, int& cardWidthScaled, int&cardHeightScaled) const;

    public:
        DiscardPile(SDL_Renderer* renderer);
        DiscardPile();
        Card drawCard();
        void discardCard(Card card);
        bool isEmpty() const {
            return discardTop>= 52;
        }
        void render(SDL_Renderer* renderer, Settings* settings) const;
};

#endif