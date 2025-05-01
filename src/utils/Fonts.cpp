#include "cpp-card-game/Fonts.hpp"

namespace Fonts {
    TTF_Font* Small = nullptr;
    TTF_Font* Medium = nullptr;
    TTF_Font* Large = nullptr;
    TTF_Font* Title = nullptr;

    bool LoadFonts() {
        Small  = TTF_OpenFont("fonts/Jersey10-Regular.ttf", 24);
        Medium = TTF_OpenFont("fonts/Jersey10-Regular.ttf", 30);
        Large  = TTF_OpenFont("fonts/Jersey10-Regular.ttf", 50);
        Title = TTF_OpenFont("fonts/Jersey10-Regular.ttf", 100);

        return Small && Medium && Large && Title;
    }

    void UnloadFonts() {
        if (Small)  { TTF_CloseFont(Small); Small = nullptr; }
        if (Medium) { TTF_CloseFont(Medium); Medium = nullptr; }
        if (Large)  { TTF_CloseFont(Large); Large = nullptr; }
        if (Title)  { TTF_CloseFont(Title); Title = nullptr; }
    }
}
