#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>

//#define DEBUG

namespace UserEvents {
	inline Uint32 GAME_WON = SDL_RegisterEvents(1);
	inline Uint32 GAME_LOST = SDL_RegisterEvents(1);
	inline Uint32 NEW_GAME = SDL_RegisterEvents(1);
	inline Uint32 GUESS_MADE = SDL_RegisterEvents(1);
	inline Uint32 COLOR_CHANGED = SDL_RegisterEvents(1);
	inline Uint32 NEXT_ROUND = SDL_RegisterEvents(1);
	inline Uint32 GUESS_VALIDATED = SDL_RegisterEvents(1);
}
namespace Config {
	//Window Settings
	inline const std::string GAME_NAME{ "Mastermind" };
	inline constexpr int WINDOW_HEIGHT{ 720 };
	inline constexpr int WINDOW_WIDTH{ 480 };
	

	//Colors
	inline const std::vector<SDL_Color> COLORS{
		/* 0 */ {255, 0, 0, 255},
		/* 1 */ {0, 255, 0, 255},
		/* 2 */ {0, 0, 255, 255},
		/* 3 */ {255, 255, 0, 255},
		/* 4 */ {255, 165, 0, 255},
		/* 5 */ {136, 0, 204, 255},
		/* 6 */ {0, 230, 230, 255}
	};
	inline constexpr SDL_Color BACKGROUND_COLOR{ 170,170,170,255 };
	inline constexpr SDL_Color BUTTON_COLOR{ 200,200,200,255 };
	inline constexpr SDL_Color BUTTON_HOVER_COLOR{ 220,220,220,255 };
	inline constexpr SDL_Color FONT_COLOR{ 0,0,0,255 };
	inline constexpr SDL_Color CLUE_BG_COLOR{ 75,75,75,255 };
	inline constexpr SDL_Color CLUE_EXACT_COLOR{ 255,0,0,255 };
	inline constexpr SDL_Color CLUE_CLOSE_COLOR{ 255,255,255,255 };

	//Game Settings
	inline constexpr int ROUNDS{ 10 };
	inline constexpr int GRID_COLUMNS{ 4 };
	inline constexpr int GRID_ROWS{ ROUNDS };
	//Grid settings
	inline constexpr int PADDING{ 5 };
	inline constexpr int CELL_SIZE{ 50 };

	inline constexpr int GRID_HEIGHT{
	  CELL_SIZE * GRID_ROWS
	  + PADDING * (GRID_ROWS - 1)
	};

	inline constexpr int GRID_WIDTH{
	  CELL_SIZE * GRID_COLUMNS +
	  PADDING * (GRID_COLUMNS - 1) };

	//Asset Paths
	inline const std::string FONT{ "Rubik-SemiBold.ttf" };
}