#ifndef CARD_H
#define CARD_H

#include <string>
#include <SDL.h>
#include "../Settings.hpp"

class Card {
    private:
        int suit; // 0: Hearts, 1: Diamonds, 2: Clubs, 3: Spades
        int rank; // 1-13 (Ace to King)
        std::string imagePath;
        std::shared_ptr<SDL_Texture> faceTexture;
        std::shared_ptr<SDL_Texture> backTexture;
        SDL_Rect dstRect;
        void loadFaceTexture(SDL_Renderer* renderer);
        void loadBackTexture(SDL_Renderer* renderer);
        
        

    public:
    void calculateCardDimensions(Settings* settings, int& cardWidthScaled, int&cardHeightScaled) const;
        int getSuit() const;
        int getRank() const;
        std::string getSuitString() const;
        std::string getRankString(bool asInt) const;
        std::string getCardString() const;
        std::string getCardImagePath() const;

        Card(int suit, int rank, SDL_Renderer* renderer);
        Card() = default;
        ~Card() {
        
        }

        bool setSuit(int suit);
        bool setRank(int rank);

        int getCardScore() const;

        void renderFace(SDL_Renderer* renderer) const;
        void renderBack(SDL_Renderer* renderer) const;

        void updateCardRect(Settings* settings, int x, int y);
        bool isClicked(int mouseX, int mouseY) const;
};

#endif