#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "Card.hpp"
#include "Deck.hpp"
#include <vector>

class Player {
    private:
        std::vector<Card> hand;
        std::vector<Card> playableCards;

        int visableCards = 0b0000;
        SDL_Rect handBackgroundRect;

        void updateHandBackgroundRect(Settings* settings);\
        void updateCardRect(Settings* settings);

        void renderHandBackground(SDL_Renderer* renderer) const;

        int getHandBackgroundXCoord(Settings* settings) const {
            return settings->screenWidth / 16;
        }
        int getHandBackgroundYCoord(Settings* settings) const {
            return settings->screenHeight / 3 * 2;
        }
        int getHandBackgroundWidth(Settings* settings) const {
            return settings->screenWidth /2;
        }
        int getHandBackgroundHeight(Settings* settings) const {
            return settings->screenHeight / 3;
        }

        int getHandYCoord(Settings* settings) const {
            return settings->screenHeight / 3 * 2 + 20;
        }
        int getHandXCoord(Settings* settings, int padding) const {
            return (padding >= 0) ? settings->screenWidth / 16 + padding : settings->screenWidth / 16;
        }
        int getHandCardPadding(Settings* settings, int cardWidth) const {
            return (settings->screenWidth / (hand.size()*2) - cardWidth) / 2;
        }
        int getHandCardSpacing(int cardWidth, int padding) const {
            return cardWidth + padding*2;
        }

    
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

        
        void showClickedCards(int mouseX, int mouseY);
        void hideClickedCards(int mouseX, int mouseY);

        int getVisableCards() const {
            unsigned int uCount;

            uCount = visableCards - ((visableCards >> 1) & 033333333333) - ((visableCards >> 2) & 011111111111);
            return ((uCount + (uCount >> 3)) & 030707070707) % 63;
            return uCount;
        }

        void update(Settings* settings) {
            updateCardRect(settings);
            updateHandBackgroundRect(settings);
        }

};
#endif