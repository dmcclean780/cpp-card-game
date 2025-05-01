#include "cpp-card-game/game-components/Player.hpp"
#include <iostream>

Player::Player() {
    for (int i = 0; i < 4; ++i) {
        hand[i] = Card();
    }
}

bool Player::addCardToHand(const Card& card) {
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRank() == 0) { // Check for an empty slot
            hand[i] = card;            return true;
        }
    }
    std::cerr << "Hand is full. Cannot add more cards." << std::endl;
    return false;
}

bool Player::removeCardFromHand(int index) {
    if (index < 0 || index >= 4) {
        std::cerr << "Invalid index: " << index << std::endl;
        return false;
    }
    hand[index] = Card(); // Reset the card to an empty state
    return true;
}

void Player::printHand() const {
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRank() != -1) { // Only print non-empty cards
            std::cout << hand[i].getCardString() << std::endl;
        }
    }
}

int Player::getHandSize() const {
    int size = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRank() != -1) {
            ++size;
        }
    }
    return size;
}

Card Player::getCardFromHand(int index) const {
    if (index < 0 || index >= 4) {
        std::cerr << "Invalid index: " << index << std::endl;
        return Card(); // Return an empty card
    }
    return hand[index];
}

bool Player::swapCard(int index, const Card& newCard) {
    if (index < 0 || index >= 4) {
        std::cerr << "Invalid index: " << index << std::endl;
        return false;
    }
    hand[index] = newCard;
    return true;
}

int Player::getHandScore() const {
    int score = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRank() != -1) {
            score += hand[i].getCardScore();
        }
    }
    return score;
}

void Player::renderHandVisable(SDL_Renderer* renderer) const {
    for (int i = 0; i < 4; i++) {
        Card card = hand[i];
        card.renderFace(renderer); // Adjust the x-coordinate for spacing
    }
}

void Player::renderHandHidden(SDL_Renderer* renderer) const {
    for (int i = 0; i < 4; i++) {
        Card card = hand[i];
        card.renderBack(renderer); // Adjust the x-coordinate for spacing
    }
}

void Player::renderHand(SDL_Renderer* renderer) const {
    for (int i = 0; i < 4; i++) {
        Card card = hand[i];
        if((visableCards  & (0b1 << i)) >> i == 1) {
            card.renderFace(renderer); // Adjust the x-coordinate for spacing
        } else {
            card.renderBack(renderer); // Adjust the x-coordinate for spacing
        }
    }
}

void Player::updateCardRect(Settings* settings) {
    int cardWidthScaled, cardHeightScaled;
    int handYCoord = settings->screenHeight / 3 * 2;
    int handXStart = settings->screenWidth / 4;
    int handXGap = settings->screenWidth / 8;
    for (int i = 0; i < 4; i++) {
        hand[i].updateCardRect(settings,  handXStart + (i * handXGap), handYCoord); // Update the card rectangle with the new dimensions
    }
}

void Player::showClickedCards(int mouseX, int mouseY) {
    for (int i = 0; i < 4; i++) {
        if (hand[i].isClicked(mouseX, mouseY)) {
            visableCards ^= (0b1 << i);
        }
    }
}

void Player::hideClickedCards(int mouseX, int mouseY) {
    for (int i = 0; i < 4; i++) {
        if (hand[i].isClicked(mouseX, mouseY)) {
            visableCards &= ~(0b1 << i);
        }
    }
}