#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Rectangle.h"
#include "Config.h"

/// <summary>
/// Handles the display of the clue pegs alongside the grid.
/// </summary>
class ClueDisplay {
public:
	//Render each hintbox
	void Render(SDL_Surface* Surface) {
		SDL_FillRect(
			Surface, &BackgroundRect, SDL_MapRGB(
				Surface->format, BackgroundColor.r, BackgroundColor.g,
				BackgroundColor.b
			)
		);

		for (auto& Element : ClueRects) {
			SDL_FillRect(
				Surface, Element.GetRect(), SDL_MapRGB(
					Surface->format, Element.GetColor().r, Element.GetColor().g,
					Element.GetColor().b
				)
			);
		}
	}

	//Handle Events
	void HandleEvent(const SDL_Event& E) {
		if (E.type == UserEvents::GUESS_VALIDATED) {
			HandleGuess(E.user);
		}
		else if (E.type == UserEvents::NEW_GAME) {
			Reset();
		}
	}

	//Get the current guess result and add clue rects to the UI based on the guess.
	void HandleGuess(const SDL_UserEvent& E) {
		GameManager* Guess{ static_cast<GameManager*>(E.data1) };

		std::vector<int> Results = Guess->GetResult();

		AddClueRects(Results[0], Results[1]);
	}

	//Add clue pips to the clue bar based on the amount of correct and incorrect guesses.
	void AddClueRects(int Exact, int Close) {
		//Get how many exact guesses there were
		int CountExact = Exact;
		//Display the exact guesses
		for (int i { 1 }; i <=  Exact + Close; i++) {
			if (CountExact > 0) {
				CreateClueRect(i, true);
				--CountExact;
			}
			//When there are no more exact guesses, add the close guesses.
			else {
				CreateClueRect(i, false);
			}
		}
		//Increment the round counter
		++Count;
	}

	//Reset for a new game
	void Reset() {
		Count = 0;
		ClueRects.clear();
	}
	
	//Create a clue rect with the color based on if it was exactly right or not.
	void CreateClueRect(int offset, bool exact) {
		SDL_Color Color = exact ? Config::CLUE_EXACT_COLOR : Config::CLUE_CLOSE_COLOR;
		ClueRects.emplace_back(
			Engine::Rectangle{
				BackgroundRect.x + Config::PADDING * 4 * offset,
				(BackgroundRect.h - Config::PADDING / 2 - Config::CELL_SIZE / 2) - Config::CELL_SIZE * Count,
				Config::CELL_SIZE / 4,
				Config::CELL_SIZE / 4,
				Color
			}
		);
	}

private:
	//Amount of clue rectangles
	int Count{ 0 };
	SDL_Rect BackgroundRect{ 
		Config::GRID_WIDTH + Config::CELL_SIZE * 3,
		Config::PADDING,
		Config::GRID_WIDTH / Config::GRID_COLUMNS * 2,
		Config::GRID_HEIGHT - Config::CELL_SIZE + Config::PADDING 
	};

	SDL_Color BackgroundColor{ Config::CLUE_BG_COLOR };
	std::vector<Engine::Rectangle> ClueRects{};
};