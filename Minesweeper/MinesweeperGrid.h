#pragma once
#pragma once
#include <vector>
#include "Globals.h"
#include "MinesweeperCell.h"
#include "Random.h"

class MinesweeperGrid {
public:
	//Construct a grid of size x by y cells
	MinesweeperGrid(int x, int y) {
		using namespace Config;
		Children.reserve(GRID_COLUMNS * GRID_ROWS);
		for (int Col{ 1 }; Col <= GRID_COLUMNS; ++Col) {
			for (int Row{ 1 }; Row <= GRID_ROWS; ++Row) {
				constexpr int Spacing{ CELL_SIZE + PADDING };
				Children.emplace_back(
					x + (Spacing) * (Col - 1),
					y + (Spacing) * (Row - 1),
					CELL_SIZE, CELL_SIZE, Row, Col
				);
			}
		}
		PlaceBombs();
	}

	//Render each cell
	void Render(SDL_Surface* Surface) {
		for (auto& Child : Children) {
			Child.Render(Surface);
		}
	}

	
	void HandleEvent(const SDL_Event& E) {
		if (E.type == UserEvents::CELL_CLEARED) {
			HandleCellCleared(E.user);
		}
		//Reset all grid cells and place new bombs when a new game is started.
		else if (E.type == UserEvents::NEW_GAME) {
			for (auto& Child : Children) {
				Child.Reset();
			}
			PlaceBombs();
		}
		//Forward events to the individual grid cells
		for (auto& Child : Children) {
			Child.HandleEvent(E);
		}
	}

	
private:
	int CellsToClear;
	std::vector<MinesweeperCell> Children;

	//Populate the grid with bombs.
	void PlaceBombs() {
		int BombsToPlace{ Config::BOMB_COUNT };
		CellsToClear = Config::GRID_COLUMNS * Config::GRID_ROWS - Config::BOMB_COUNT;
		while (BombsToPlace > 0) {
			//Select a random index to place a bomb onto
			const size_t RandomIndex{ Engine::Random::Int(0, Children.size() - 1) };
			//Place the bomb at that index
			if (Children[RandomIndex].PlaceBomb()) {
				--BombsToPlace;
			}
		}
	}

	void HandleCellCleared(const SDL_UserEvent& E) {
		auto* Cell{ static_cast<MinesweeperCell*>(E.data1) };

		if (Cell->GetHasBomb()) {
			SDL_Event Event{ UserEvents::GAME_LOST };
			SDL_PushEvent(&Event);
		}
		else {
			--CellsToClear;
			if (CellsToClear == 0) {
				SDL_Event Event{ UserEvents::GAME_WON };
				SDL_PushEvent(&Event);
			}
		}
	}

	
};