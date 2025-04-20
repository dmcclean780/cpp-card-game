#ifndef COLORS_H
#define COLORS_H

#include <SDL.h>

namespace Colors {
    constexpr SDL_Color WHITE     = { 255, 255, 255, 255 };
    constexpr SDL_Color BLACK     = {   0,   0,   0, 255 };
    constexpr SDL_Color RED       = { 255,   0,   0, 255 };
    constexpr SDL_Color GREEN     = {   0, 255,   0, 255 };
    constexpr SDL_Color BLUE      = {   0,   0, 255, 255 };
    constexpr SDL_Color GRAY      = { 128, 128, 128, 255 };
    constexpr SDL_Color LIGHT_GRAY = { 200, 200, 200, 255 };
    constexpr SDL_Color DARK_GRAY  = {  50,  50,  50, 255 };
}

#endif
