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
            updateTexture(renderer);
        }
        void decrementTurnCounter(SDL_Renderer* renderer) { 
            turnCounter--; 
            updateTexture(renderer);
        }
        void resetTurnCounter(SDL_Renderer* renderer) { 
            turnCounter = 0; 
            updateTexture(renderer); 
        }
    
    private:

        void updateTexture(SDL_Renderer* renderer);


        SDL_Rect rect;
        SDL_Texture* texture;
        int turnCounter;
        SDL_Color color;
        TTF_Font* font;

    };

#endif