#include "cpp-card-game/game-components/Card.hpp"

#include <SDL_image.h>

#include <iostream>

#include "cpp-card-game/Colors.hpp"

Card::Card(int suit, int rank, SDL_Renderer *renderer)
    : suit(suit), rank(rank) {
  if (suit < 0 || suit > 3 || rank < 1 || rank > 13) {
    std::cerr << "Invalid card values. Suit: " << suit << ", Rank: " << rank
              << std::endl;
    this->suit = -1;
    this->rank = -1;
  } else {
    imagePath = "../assets/cards/card-" + getSuitString() + "-" + getRankString(true) + ".png";

    loadFaceTexture(renderer);
    if (!faceTexture) {
      std::cerr << "Failed to load face texture for card: " << getCardString() << std::endl;
    }
    loadBackTexture(renderer);
    if (!backTexture) {
      std::cerr << "Failed to load back texture for card: " << getCardString() << std::endl;
    }
  }
}

void Card::loadBackTexture(SDL_Renderer *renderer) {
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

void Card::loadFaceTexture(SDL_Renderer *renderer) {
  SDL_Surface *loadedSurface = IMG_Load(imagePath.c_str());
  if (!loadedSurface) {
    std::cerr << "Failed to load image: " << IMG_GetError() << '\n';
  }

  faceTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface), SDL_DestroyTexture);
  if (!faceTexture) {
    std::cerr << "Failed to create faceTexture: " << SDL_GetError() << '\n';
  }

  SDL_FreeSurface(loadedSurface);
}

int Card::getSuit() const { return suit; }

int Card::getRank() const { return rank; }

std::string Card::getSuitString() const {
  // std::cout << "getSuitString: " << suit << std::endl;
  switch (suit) {
  case 0:
    return "hearts";
  case 1:
    return "diamonds";
  case 2:
    return "clubs";
  case 3:
    return "spades";
  default:
    return "invalid";
  }
}

std::string Card::getRankString(bool asInt) const {
  if (asInt) {
    return std::to_string(rank);
  }
  switch (rank) {
  case 1:
    return "ace";
  case 11:
    return "jack";
  case 12:
    return "queen";
  case 13:
    return "king";
  default:
    return std::to_string(rank);
  }
}

std::string Card::getCardString() const {
  return getRankString(false) + " of " + getSuitString();
}

std::string Card::getCardImagePath() const { return imagePath; }

bool Card::setSuit(int suit) {
  if (suit < 0 || suit > 3) {
    std::cerr << "Invalid suit value: " << suit << std::endl;
    return false;
  }
  this->suit = suit;
  return true;
}

bool Card::setRank(int rank) {
  if (rank < 1 || rank > 13) {
    std::cerr << "Invalid rank value: " << rank << std::endl;
    return false;
  }
  this->rank = rank;
  return true;
}

int Card::getCardScore() const {
  if (rank == 1) { // Ace
    return 0;
  } else if (rank == 13 && (suit == 0 || suit == 1)) { // Face cards
    return -1;
  } else {
    return rank; // Number cards
  }
}

void Card::renderFace(SDL_Renderer *renderer) const {
  if (faceTexture) {
    SDL_RenderCopy(renderer, faceTexture.get(), NULL, &dstRect);
  } else {
    std::cerr << "Texture not loaded for card: " << getCardString() << std::endl;
  }
}

void Card::renderBack(SDL_Renderer *renderer) const {
 if (backTexture) {
    SDL_RenderCopy(renderer, backTexture.get(), NULL, &dstRect);
  } else {
    std::cerr << "Texture not loaded for card: " << getCardString() << std::endl;
  }
}

void Card::calculateCardDimensions(Settings* settings, int& cardWidthScaled, int& cardHeightScaled) const {
    int cardHeightMaximum = settings->screenHeight / 3; // Set the height of the card
    int cardWidthMaximum = settings->screenWidth / 8;   // Set the width of the card
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

void Card::updateCardRect(Settings* settings, int x, int y) {
    int cardWidthScaled;
    int cardHeightScaled;
    calculateCardDimensions(settings, cardWidthScaled, cardHeightScaled);
    dstRect = {x, y, cardWidthScaled, cardHeightScaled};
}

bool Card::isClicked(int mouseX, int mouseY) const {
  return (mouseX > dstRect.x && mouseX < dstRect.x + dstRect.w &&
          mouseY > dstRect.y && mouseY < dstRect.y + dstRect.h);
}