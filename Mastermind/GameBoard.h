#pragma once
#include <vector>
#include "Config.h"
#include "MastermindCell.h"
#include "GameManager.h"

/// <summary>
/// Handles rendering and game logic for the game board.
/// </summary>
class GameBoard {
public:
	//Construct a grid at position x , y
	GameBoard(int x, int y) {
		using namespace Config;
		Cells.reserve(GRID_COLUMNS * GRID_ROWS);
		for (int Row{ GRID_ROWS }; Row >= 1; --Row) {
			for (int Col{ GRID_COLUMNS }; Col >= 1; --Col) {
				constexpr int Spacing{ CELL_SIZE };
				Cells.emplace_back(
					x + (Spacing) * (Col - 1),
					y + (Spacing) * (Row - 1),
					CELL_SIZE, CELL_SIZE, Row, Col
				);
			}
		}
		Manager.GenerateCode();
		//Cells start disabled, so we enable the first ones.
		NextRound(1);
	}

	//Render each cell
	void Render(SDL_Surface* Surface) {
		for (auto& Child : Cells) {
			Child.Render(Surface);
		}
	}


	void HandleEvent(const SDL_Event& E) {
		//User selected a new color
		if (E.type == UserEvents::COLOR_CHANGED) {
			HandleColorChanged(E.user);
		}
		//New game started.
		else if (E.type == UserEvents::NEW_GAME) {
			for (auto& Child : Cells) {
				Child.Reset();
			}
			Manager.Reset();
			//Cells start disabled, so we enable the first ones.
			NextRound(1);
		}
		else if (E.type == UserEvents::NEXT_ROUND) {
			NextRound(Manager.NextRound());
		}
		//Forward events to the individual grid cells
		for (auto& Child : Cells) {
			Child.HandleEvent(E);
		}

		Manager.HandleEvent(E);
	}

	void NextRound(int round) {
		using namespace Config;
		//If this is the last round, don't do anything.
		if (round > ROUNDS) {
			return;
		}
		//Set all cells to inactive.
		for (auto& element : Cells) {
			element.SetActive(false);
		}
		//Find the starting cell offset
		int start = (round - 1) * GRID_COLUMNS;
		//The goal will always by 1 column width ahead.
		int goal = start + GRID_COLUMNS;
		//Activate the next row.
		for (; start < goal; ++start) {
			Cells[start].SetActive(true);
			Cells[start].SetColor(SDL_Color{ 100,100,100,255 });
		}
	}

	

private:
	std::vector<MastermindCell> Cells;
	GameManager Manager; //We couple the game manager with the board. While this makes the organization a little more complicated, its more convenient

	void HandleColorChanged(const SDL_UserEvent& E) {
		auto* Cell{ static_cast<MastermindCell*>(E.data1) };
		//Get which cell was changed. The column aligns with the index.
		int Index = Cell->GetCol();
		//Set the guess info to the new color
		Manager.SetGuess(Index, Cell->GetColor());
	}
};