#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Settings {
    bool fullscreen;
    int screenWidth;
    int screenHeight;
};

inline void to_json(json& j, const Settings& s) {
    j = json{
        {"FULLSCREEN", s.fullscreen},
        {"SCREEN_WIDTH", s.screenWidth},
        {"SCREEN_HEIGHT", s.screenHeight}
    };
}

inline void from_json(const json& j, Settings& s) {
    j.at("FULLSCREEN").get_to(s.fullscreen);
    j.at("SCREEN_WIDTH").get_to(s.screenWidth);
    j.at("SCREEN_HEIGHT").get_to(s.screenHeight);
}

#include <fstream>

inline Settings loadSettings(const std::string& path) {
    std::ifstream inFile(path);
    json j;
    inFile >> j;

    return j.get<Settings>();
}

inline void saveSettings(const std::string& path, const Settings& settings) {
    std::ofstream outFile(path);
    json j = settings;
    outFile << j.dump(4); // pretty print with indent of 4
}

#endif // SETTINGS_HPP