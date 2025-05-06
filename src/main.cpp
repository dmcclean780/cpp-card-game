#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "cpp-card-game/ui/Button.hpp"
#include "cpp-card-game/Colors.hpp"
#include "cpp-card-game/Fonts.hpp"
#include "cpp-card-game/ScreenManager.hpp"
#include "cpp-card-game/Settings.hpp"
#include "cpp-card-game/screens/StartingScreen.hpp"

int main() {

  srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

  Settings settings = loadSettings("config/settings.json");
  saveSettings("config/settings.json", settings); // save it back

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  Fonts::LoadFonts();

  SDL_Window *window = SDL_CreateWindow("Start Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
  settings.screenWidth = 800;
  settings.screenHeight = 600;

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  ScreenManager manager;
  manager.setScreen(std::make_unique<StartingScreen>(renderer, &manager));

  SDL_Event event;
  bool running = true;

  while (running) {

    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_QUIT) {
        saveSettings("config/settings.json", settings); // save it back
        running = false;
      }

      manager.handleEvents(event, renderer, &settings);
    }

    manager.update(renderer, &settings);
    manager.render(renderer, &settings);
    manager.applyPendingScreenChange(window, &settings);
    SDL_RenderPresent(renderer);
  }

  Fonts::UnloadFonts();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
