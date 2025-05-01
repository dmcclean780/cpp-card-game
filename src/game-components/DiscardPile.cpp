#include "cpp-card-game/game-components/DiscardPile.hpp"
#include <iostream>
#include <SDL_image.h>
#include "cpp-card-game/Colors.hpp"

DiscardPile::DiscardPile(SDL_Renderer* renderer) {
    DiscardPile();
    loadBackTexture(renderer);
}

DiscardPile::DiscardPile() {
    for (int i = 0; i < 52; ++i) {
        discardPile[i] = Card(); // Initialize each card to an empty state
    }
}

Card DiscardPile::drawCard() {
    if(discardTop >= 52) {
        std::cerr << "No more cards in the deck." << std::endl;
        return Card(); // Return an empty card
    }
    Card card = discardPile[discardTop++];
    return card;

}

void DiscardPile::render(SDL_Renderer *renderer, Settings *settings) const {
    int cardWidthScaled;
    int cardHeightScaled;

    int discardYCoord = settings->screenHeight / 3;
    int discardXCoord = (settings->screenWidth / 3) * 2;

    if (backTexture) {
        calculateCardDimensions(settings, cardWidthScaled, cardHeightScaled);
        discardXCoord -= cardWidthScaled;
        SDL_Rect dstRect = {discardXCoord, discardYCoord, cardWidthScaled, cardHeightScaled};
        
        if(isEmpty()){
            SDL_SetRenderDrawColor(renderer, Colors::DARK_GRAY.r, Colors::DARK_GRAY.g, Colors::DARK_GRAY.b, Colors::DARK_GRAY.a);
            SDL_RenderFillRect(renderer, &dstRect);
        } else {
            SDL_RenderCopy(renderer, backTexture.get(), NULL, &dstRect);
        }
        
    } else {
        std::cerr << "Texture not loaded for deck." << std::endl;
    }
}

void DiscardPile::loadBackTexture(SDL_Renderer *renderer) {
    std::string backImagePath = "../assets/cards/card-back.png";
    SDL_Surface *loadedSurface = IMG_Load(backImagePath.c_str());
    if (!loadedSurface) {
      std::cerr << "Failed to load image: " << IMG_GetError() << '\n';
    }
  
    backTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface), SDL_DestroyTexture);
    if (!backTexture) {
      std::cerr << "Failed to create bsckTexture: " << SDL_GetError() << '\n';
    }
  
    SDL_FreeSurface(loadedSurface);
}

void DiscardPile::calculateCardDimensions(Settings* settings, int& cardWidthScaled, int&cardHeightScaled) const {
    int cardHeightMaximum = settings->screenHeight / 3; // Set the height of the card
    int cardWidthMaximum = settings->screenWidth / 4;   // Set the width of the card
    int cardWidthOriginal;
    int cardHeightOriginal;
    int cardWidthScalingFactor;
    int cardHeightScalingFactor;

    SDL_QueryTexture(backTexture.get(), NULL, NULL, &cardWidthOriginal, &cardHeightOriginal);

    cardWidthScalingFactor = cardWidthMaximum / cardWidthOriginal;
    cardHeightScalingFactor = cardHeightMaximum / cardHeightOriginal;
    if (cardWidthScalingFactor < cardHeightScalingFactor) {
        cardWidthScaled = cardWidthOriginal * cardWidthScalingFactor;
        cardHeightScaled = cardHeightOriginal * cardWidthScalingFactor;
    } else {
        cardHeightScaled = cardHeightOriginal * cardHeightScalingFactor;
        cardWidthScaled = cardWidthOriginal * cardHeightScalingFactor;
    }
}