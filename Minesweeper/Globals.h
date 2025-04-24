#pragma once

//#define DEBUG

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
namespace UserEvents {
	inline Uint32 CELL_CLEARED = SDL_RegisterEvents(1);
	inline Uint32 BOMB_PLACED = SDL_RegisterEvents(1);
	inline Uint32 GAME_WON = SDL_RegisterEvents(1);
	inline Uint32 GAME_LOST = SDL_RegisterEvents(1);
	inline Uint32 NEW_GAME = SDL_RegisterEvents(1);
	inline Uint32 FLAG_PLACED = SDL_RegisterEvents(1);
	inline Uint32 FLAG_CLEARED = SDL_RegisterEvents(1);
}

namespace Config {
	//Game settings
	inline const std::string GAME_NAME{ "Minesweeper Clone" };
	inline constexpr int GRID_COLUMNS{ 8 };
	inline constexpr int GRID_ROWS{ 4 };
	inline constexpr int BOMB_COUNT{ 6 };

	//Assertion for bomb count
	static_assert(BOMB_COUNT < (GRID_COLUMNS * GRID_ROWS), 
		"Cannot place more bombs than grid cells!");

	//Grid settings
	inline constexpr int PADDING{ 5 };
	inline constexpr int CELL_SIZE{ 50 };

	//Grid size calculation
	inline constexpr int GRID_HEIGHT{
	  CELL_SIZE * GRID_ROWS
	  + PADDING * (GRID_ROWS - 1)
	};
	inline constexpr int GRID_WIDTH{
	  CELL_SIZE * GRID_COLUMNS +
	  PADDING * (GRID_COLUMNS - 1) };
	
	//Window Settings
	inline constexpr int FOOTER_HEIGHT{ 60 };
	inline constexpr int FLAG_COUNTER_WIDTH{ 100 };
	inline constexpr int WINDOW_HEIGHT{
	GRID_HEIGHT + FOOTER_HEIGHT
	+ PADDING * 2
	};
	inline constexpr int WINDOW_WIDTH{
	  GRID_WIDTH + PADDING * 2
	};
	

	//Colors
	inline constexpr SDL_Color BACKGROUND_COLOR{ 170,170,170,255 };
	inline constexpr SDL_Color BUTTON_COLOR{ 200,200,200,255 };
	inline constexpr SDL_Color BUTTON_HOVER_COLOR{ 220,220,220,255 };
	inline constexpr SDL_Color BUTTON_CLEARED_COLOR{240, 240, 240, 255 };
	inline constexpr SDL_Color BUTTON_SUCCESS_COLOR{210, 235, 210, 255 };
	inline constexpr SDL_Color BUTTON_FAILURE_COLOR{235, 210, 210, 255 };
	inline constexpr SDL_Color FLAG_COUNTER_COLOR{80, 80, 80, 255 };
	// Text color based on number of surrounding bombs.
	inline const std::vector<SDL_Color> TEXT_COLORS{
		/* 0 */ {0, 0, 0, 255}, // Unused
		/* 1 */ {0, 1, 249, 255},
		/* 2 */ {1, 126, 1, 255},
		/* 3 */ {250, 1, 2, 255},
		/* 4 */ {1, 0, 128, 255},
		/* 5 */ {129, 1, 0, 255},
		/* 6 */ {0, 128, 128, 255},
		/* 7 */ {0, 0, 0, 255},
		/* 8 */ {128, 128, 128, 255}
	};

	//Asset Paths
	inline const std::string FONT{ "Rubik-SemiBold.ttf" };
	inline const std::string BOMB_IMAGE{ "Bomb.png" };
	inline const std::string FLAG_IMAGE{ "Flag.png" };
}

//Utilities for developer build
namespace Utils {
	#ifdef DEBUG
	inline void CheckSDLError(const std::string& Msg) {
		const char* error = SDL_GetError();
		if (*error != '\0') {
			std::cerr << Msg << "Error: " << error << '\n';
			SDL_ClearError();
		}
	}
	#endif
}
