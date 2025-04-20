#include "cpp-card-game/Button.hpp"
#include "cpp-card-game/Colors.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Start Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("fonts/Jersey10-Regular.ttf", 28); // Load your own TTF font
    
    
    Button startButton(300, 250, "Start Game", font, Colors::WHITE, renderer);

    bool running = true;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear with black
        SDL_RenderClear(renderer);
        
        // Draw button text on top
        startButton.render(renderer);
        
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (startButton.isClicked(x, y)) {
                    std::cout << "Start Game clicked!\n";
                    running = false; // In real case, you'd switch to the game loop
                }
            }
        }
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
