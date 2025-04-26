#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define DEBUG
namespace UserEvents {
    inline Uint32 ADVANCE{ SDL_RegisterEvents(1) };
    inline Uint32 APPLE_EATEN{ SDL_RegisterEvents(1) };
    inline Uint32 RESTART_GAME{ SDL_RegisterEvents(1) };
    inline Uint32 GAME_WON{ SDL_RegisterEvents(1) };
    inline Uint32 GAME_LOST{ SDL_RegisterEvents(1) };
}
namespace Config {
    //Window Settings
    inline const std::string GAME_NAME{ "Snake" };

    inline constexpr int GRID_COLUMNS{ 16 };
    static_assert(GRID_COLUMNS >= 12,
        "Grid must be at least 12 columns wide");

    inline constexpr int GRID_ROWS{ 5 };
    static_assert(GRID_ROWS >= 5,
        "Grid must be at least 5 rows tall");

    //Size and Positioning
    inline constexpr int CELL_SIZE{ 36 };
    inline constexpr int GRID_HEIGHT{ CELL_SIZE * GRID_ROWS };
    inline constexpr int GRID_WIDTH{ CELL_SIZE * GRID_COLUMNS };
    inline constexpr int PADDING{ 5 };
    inline constexpr int FOOTER_HEIGHT{ 60 };
    inline constexpr int WINDOW_HEIGHT{ GRID_HEIGHT + FOOTER_HEIGHT + PADDING * 2 };
    inline constexpr int WINDOW_WIDTH{ GRID_WIDTH + PADDING * 2 };
    
    //Colors
    inline constexpr SDL_Color BACKGROUND_COLOR{ 85, 138, 52, 255 };
    inline constexpr SDL_Color FONT_COLOR{ 255, 255, 255, 255 };
    inline constexpr SDL_Color CELL_COLOR_A{ 170, 215, 80, 255 };
    inline constexpr SDL_Color CELL_COLOR_B{ 160, 200, 80, 255 };
    inline constexpr SDL_Color SNAKE_COLOR{ 70, 120, 200, 255 };
    inline constexpr SDL_Color SNAKE_LOST_COLOR{ 227, 67, 97, 255 };
    inline constexpr SDL_Color SNAKE_VICTORY_COLOR{ 255, 140, 0, 255 };
    inline constexpr SDL_Color BUTTON_COLOR{ 73, 117, 46, 255 };
    inline constexpr SDL_Color BUTTON_HIGHLIGHT_COLOR{ 67, 117, 234, 255 };
    inline constexpr SDL_Color SCORE_BACKGROUND_COLOR{ 73, 117, 46, 255 };
    //Assets
    inline const std::string APPLE_IMAGE{ "Apple.png" };
    inline const std::string FONT{ "Rubik-SemiBold.ttf" };
    //Game Settings
    inline constexpr int ADVANCE_INTERVAL{ 200 };
    inline constexpr int MAX_LENGTH{GRID_COLUMNS * GRID_ROWS }; //Length at which the player is considered to have won.
}

inline void CheckSDLError(
    const std::string& Msg) {
#ifdef DEBUG
    const char* error = SDL_GetError();
    if (*error != '\0') {
        std::cerr << Msg << " Error: " << error << '\n';
        SDL_ClearError();
    }
#endif
}