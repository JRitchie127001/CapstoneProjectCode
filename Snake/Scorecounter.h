#pragma once
#include <SDL2/SDL.h>
#include "Assets.h"
#include "Text.h"

class ScoreCounter {
public:
	ScoreCounter(Assets& Assets) : Assets{ Assets } {}
	void HandleEvent(SDL_Event& E) {
		//Increment the score when an apple is eaten.
		if (E.type == UserEvents::APPLE_EATEN) {
			++CurrentScore;
			Text.SetText(GetScoreString());
		}
		//Reset the score on game restart.
		else if (E.type == UserEvents::RESTART_GAME) {
			CurrentScore = 0;
			Text.SetText(GetScoreString());
		}
	}
	void Render(SDL_Surface* Surface) {
		using namespace Config;
		SDL_FillRect(Surface, &BackgroundRect,
			SDL_MapRGB(Surface->format,
				SCORE_BACKGROUND_COLOR.r,
				SCORE_BACKGROUND_COLOR.g,
				SCORE_BACKGROUND_COLOR.b
			));
		//Render the apple icon and current score.
		Assets.Apple.Render(Surface, &AppleRect);
		Text.Render(Surface, &TextRect);
	}
private:
	
	int CurrentScore{ 0 };
	int MaxScore{ Config::MAX_LENGTH - 2 }; //Since the snake starts with 2 segments we subtract 2 from the max.

	Assets& Assets;
	Text Text{ GetScoreString(), 40 };

	SDL_Rect BackgroundRect{
		Config::PADDING,
		Config::GRID_HEIGHT + Config::PADDING * 2,
		MaxScore > 99 ? 250 : 190,
		Config::FOOTER_HEIGHT - Config::PADDING
	};
	SDL_Rect AppleRect{
		BackgroundRect.x + Config::PADDING,
		BackgroundRect.y + Config::PADDING,
		BackgroundRect.h - Config::PADDING * 2,
		BackgroundRect.h - Config::PADDING * 2
	};

	SDL_Rect TextRect{
		AppleRect.x + AppleRect.w + Config::PADDING,
		AppleRect.y,
		0, 0 
	};

	//Returns the current score in the format "Current/Max"
	std::string GetScoreString() {
		return std::to_string(CurrentScore) + "/"
			+ std::to_string(MaxScore);
	}
};