#include "cpp-card-game/game-components/Player.hpp"
#include <iostream>

#include "cpp-card-game/Colors.hpp"

Player::Player() {
}

bool Player::addCardToHand(const Card& card) {
    hand.push_back(card);
    visableCards |= (0b0 << (hand.size() - 1)); // Set the last bit to 0
    return true;
}

bool Player::removeCardFromHand(int index) {
    if (index < 0 || index >= 4) {
        std::cerr << "Invalid index: " << index << std::endl;
        return false;
    }
    hand.at(index) = Card(); // Reset the card to an empty state
    return true;
}

void Player::printHand() const {
    for (int i = 0; i < hand.size(); ++i) {
        if (hand.at(i).getRank() != -1) { // Only print non-empty cards
            std::cout << hand.at(i).getCardString() << std::endl;
        }
    }
}

int Player::getHandSize() const {
    int size = 0;
    for (int i = 0; i < hand.size(); ++i) {
        if (hand.at(i).getRank() != -1) {
            ++size;
        }
    }
    return size;
}

Card Player::getCardFromHand(int index) const {
    if (index < 0 || index >= hand.size()) {
        std::cerr << "Invalid index: " << index << std::endl;
        return Card(); // Return an empty card
    }
    return hand.at(index);
}

bool Player::swapCard(int index, const Card& newCard) {
    if (index < 0 || index >= hand.size()) {
        std::cerr << "Invalid index: " << index << std::endl;
        return false;
    }
    hand.at(index) = newCard;
    return true;
}

int Player::getHandScore() const {
    int score = 0;
    for (int i = 0; i < hand.size(); ++i) {
        if (hand.at(0).getRank() != -1) {
            score += hand.at(0).getCardScore();
        }
    }
    return score;
}

void Player::renderHandVisable(SDL_Renderer* renderer) const {
    renderHandBackground(renderer); // Render the background first

    for (int i = 0; i < hand.size(); i++) {
        Card card = hand.at(i);
        card.renderFace(renderer); // Adjust the x-coordinate for spacing
    }
}

void Player::renderHandHidden(SDL_Renderer* renderer) const {
    renderHandBackground(renderer); // Render the background first

    for (int i = 0; i < hand.size(); i++) {
        Card card = hand.at(i);
        card.renderBack(renderer); // Adjust the x-coordinate for spacing
    }
}

void Player::renderHand(SDL_Renderer* renderer) const {
    renderHandBackground(renderer); // Render the background first
    for (int i = 0; i < hand.size(); i++) {
        Card card = hand.at(i);
        if((visableCards  & (0b1 << i)) >> i == 1) {
            card.renderFace(renderer); // Adjust the x-coordinate for spacing
        } else {
            card.renderBack(renderer); // Adjust the x-coordinate for spacing
        }
    }
}

void Player::renderHandBackground(SDL_Renderer* renderer) const{
    SDL_SetRenderDrawColor(renderer, Colors::DARK_GRAY.r, Colors::DARK_GRAY.g, Colors::DARK_GRAY.b, Colors::DARK_GRAY.a); // Set color to black
    SDL_RenderFillRect(renderer, &handBackgroundRect); // Fill the rectangle with the background color
}

void Player::updateHandBackgroundRect(Settings* settings) {
   
    int xStart = settings->screenWidth / 16;
    int yStart = settings->screenHeight / 3 * 2;

    int width = settings->screenWidth / 2;
    int height = settings->screenHeight / 3;

    handBackgroundRect = { xStart, yStart, width, height }; // Adjust the size and position as needed
}

void Player::updateCardRect(Settings* settings) {
    int cardWidthScaled, cardHeightScaled;
    hand[0].calculateCardDimensions(settings, cardWidthScaled, cardHeightScaled);

    int handYCoord = settings->screenHeight / 3 * 2 + 20;
    int sidePadding = (settings->screenWidth / (hand.size()*2) - cardWidthScaled) / 2;
    int handXStart = (sidePadding >= 0) ? settings->screenWidth / 16 + sidePadding : settings->screenWidth / 16;
    int handXGap = cardWidthScaled + sidePadding*2;
    for (int i = 0; i < hand.size(); i++) {
        hand[i].updateCardRect(settings,  handXStart + (i * handXGap), handYCoord); // Update the card rectangle with the new dimensions
    }

    updateHandBackgroundRect(settings); // Update the background rectangle
}

void Player::showClickedCards(int mouseX, int mouseY) {
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].isClicked(mouseX, mouseY)) {
            visableCards ^= (0b1 << i);
        }
    }
}

void Player::hideClickedCards(int mouseX, int mouseY) {
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].isClicked(mouseX, mouseY)) {
            visableCards &= ~(0b1 << i);
        }
    }
}