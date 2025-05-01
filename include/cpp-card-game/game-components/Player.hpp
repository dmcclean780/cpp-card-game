#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "Card.hpp"
#include "Deck.hpp"

class Player {
    private:
        Card hand[4];
        int visableCards = 0b0000;
    
    public:
        Player();
        bool addCardToHand(const Card& card);
        bool removeCardFromHand(int index);
        void printHand() const;
        int getHandSize() const;
        Card getCardFromHand(int index) const;
        bool swapCard(int index, const Card& newCard);
        int getHandScore() const;
        void renderHandVisable(SDL_Renderer* renderer) const;
        void renderHandHidden(SDL_Renderer* renderer) const;
        void renderHand(SDL_Renderer* renderer) const;
        void updateCardRect(Settings* settings);
        void showClickedCards(int mouseX, int mouseY);
        void hideClickedCards(int mouseX, int mouseY);
        int getVisableCards() const {
            unsigned int uCount;

            uCount = visableCards - ((visableCards >> 1) & 033333333333) - ((visableCards >> 2) & 011111111111);
            return ((uCount + (uCount >> 3)) & 030707070707) % 63;
            return uCount;
        }

};
#endif