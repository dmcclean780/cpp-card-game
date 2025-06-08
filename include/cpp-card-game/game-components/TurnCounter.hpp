#ifndef TURN_COUNTER_H
#define TURN_COUNTER_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "../Settings.hpp"

class TurnCounter {
    public:
        TurnCounter(TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
        ~TurnCounter();
    
        void render(SDL_Renderer* renderer, Settings* settings);
        int getTurnCounter() const { 
            return turnCounter; 
        }
        void incrementTurnCounter(SDL_Renderer* renderer) { 
            turnCounter++; 
            updateCounterTexture(renderer);
        }
        void decrementTurnCounter(SDL_Renderer* renderer) { 
            turnCounter--; 
            updateCounterTexture(renderer);
        }
        void resetTurnCounter(SDL_Renderer* renderer) { 
            turnCounter = 0; 
            updateCounterTexture(renderer); 
        }
    
    private:

        void updateCounterTexture(SDL_Renderer* renderer);
        void createLabelTexture(SDL_Renderer* renderer);
        void renderLabel(SDL_Renderer* renderer, Settings* settings);
        void renderCounter(SDL_Renderer* renderer, Settings* settings);
        void renderBackground(SDL_Renderer* renderer, Settings* settings);

        SDL_Texture* turnCountTexture;
        SDL_Texture* labelTexture;
        int turnCounter;
        SDL_Color color;
        TTF_Font* font;

    };

#endif