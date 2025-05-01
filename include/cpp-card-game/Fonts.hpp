#ifndef FONTS_H
#define FONTS_H

#include <SDL_ttf.h>

namespace Fonts {
    extern TTF_Font* Small;
    extern TTF_Font* Medium;
    extern TTF_Font* Large;
    extern TTF_Font* Title;

    bool LoadFonts();   // Call at startup
    void UnloadFonts(); // Call at shutdown
}

#endif
