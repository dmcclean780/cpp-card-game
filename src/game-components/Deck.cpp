#include "cpp-card-game/game-components/Deck.hpp"
#include <iostream>
#include <SDL_image.h>
#include "cpp-card-game/Colors.hpp"

Deck::Deck(SDL_Renderer* renderer) {
    int index = 0;
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 1; rank <= 13; ++rank) {
            deck[index++] = Card(suit, rank, renderer);
        }
    }
    loadBackTexture(renderer);

}

Deck::Deck() {
    for (int i = 0; i < 52; ++i) {
        deck[i] = Card(); // Initialize each card to an empty state
    }
}

void Deck::printDeck() const {
    for (const auto& card : deck) {
        std::cout << card.getCardString() << std::endl;
    }
}

void Deck::shuffleDeck() {
    for (int i = 0; i < 52; ++i) {
        int randomIndex = rand() % 52;
        std::swap(deck[i], deck[randomIndex]);
    }
}

Card Deck::drawCard() {
    if(deckTop >= 52) {
        std::cerr << "No more cards in the deck." << std::endl;
        return Card(); // Return an empty card
    }
    Card card = deck[deckTop++];
    return card;

}

void Deck::render(SDL_Renderer *renderer, Settings *settings) const {
    int deckWidthScaled;
    int deckHeightScaled;

    int deckYCoord = getDeckYCoord(settings);
    int deckXCoord = getDeckXCoord(settings);

    if (backTexture) {
        calculateDeckDimensions(settings, deckWidthScaled, deckHeightScaled);
        SDL_Rect dstRect = {deckXCoord, deckYCoord, deckWidthScaled, deckHeightScaled};
        
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

void Deck::loadBackTexture(SDL_Renderer *renderer) {
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

void Deck::calculateDeckDimensions(Settings* settings, int& deckWidthScaled, int&deckHeightScaled) const {
    int deckHeightMaximum = getDeckHeight(settings); // Set the height of the card
    int deckWidthMaximum = getDeckWidth(settings);   // Set the width of the card
    int deckWidthOriginal;
    int deckHeightOriginal;
    int deckWidthScalingFactor;
    int deckHeightScalingFactor;

    SDL_QueryTexture(backTexture.get(), NULL, NULL, &deckWidthOriginal, &deckHeightOriginal);

    deckWidthScalingFactor = deckWidthMaximum / deckWidthOriginal;
    deckHeightScalingFactor = deckHeightMaximum / deckHeightOriginal;
    if (deckWidthScalingFactor < deckHeightScalingFactor) {
        deckWidthScaled = deckWidthOriginal * deckWidthScalingFactor;
        deckHeightScaled = deckHeightOriginal * deckWidthScalingFactor;
    } else {
        deckHeightScaled = deckHeightOriginal * deckHeightScalingFactor;
        deckWidthScaled = deckWidthOriginal * deckHeightScalingFactor;
    }
}