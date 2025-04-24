#include <iostream>
#include "MinesweeperCell.h"
#include "Globals.h"

//Cosntructs each cell with its bomb info text and flag image.
MinesweeperCell::MinesweeperCell(
	int x, int y, int w, int h, int Row, int Col) :
	Button{ x, y, w, h }, Row{ Row }, Col{ Col }, BombImage{ x,y,w,h, Config::BOMB_IMAGE },
	Text{ x, y, w, h, std::to_string(AdjacentBombs), Config::TEXT_COLORS[0] },
	FlagImage{x,y,w,h,Config::FLAG_IMAGE} {};

//Event handlers for MinesweeperCells
void MinesweeperCell::HandleEvent(const SDL_Event& E) {
	//Cell Cleared
	if (E.type == UserEvents::CELL_CLEARED) {
		HandleCellCleared(E.user);
	}
	//Bomb Placed
	else if (E.type == UserEvents::BOMB_PLACED) {
		HandleBombPlaced(E.user);
	}
	//Game Win
	else if (E.type == UserEvents::GAME_WON) {
		if (hasBomb) {
			hasFlag = hasBomb;
			SetColor(Config::BUTTON_SUCCESS_COLOR);
		}
		SetIsDisabled(true);
	}
	//Game Loss
	else if (E.type == UserEvents::GAME_LOST) {
		if (hasBomb) {
			isCleared = true;
			SetColor(Config::BUTTON_FAILURE_COLOR);
		}
		SetIsDisabled(true);
	}
	Button::HandleEvent(E);
}

void MinesweeperCell::ReportEvent(uint32_t EventType) {
	SDL_Event event{ EventType };
	event.user.data1 = this;
	SDL_PushEvent(&event);
}

void MinesweeperCell::Render(SDL_Surface* Surface) {
	Button::Render(Surface);
	//Render the flag if the cell has one.
	if (hasFlag) {
		FlagImage.Render(Surface);
	}
	//Show the bomb underneath if the cell is cleared
	else if (isCleared && hasBomb) {
		BombImage.Render(Surface);
	}
	//Show the text for the amount of adjacent bombs if any exist.
	else if (isCleared && AdjacentBombs > 0) {
		Text.Render(Surface);
	}
#ifdef DEBUG
	else if (hasBomb) {
		BombImage.Render(Surface);
	}
#endif
}

//Clear the cell on left click if it is unflagged.
void MinesweeperCell::HandleLeftClick() {
	if (!hasFlag) {
		ClearCell(); 
	}
}

//Toggle the flag on a cell when the user right-clicks
void MinesweeperCell::HandleRightClick() {
	if (hasFlag) {
		ReportEvent(UserEvents::FLAG_CLEARED);
		hasFlag = false;
	}
	else {
		ReportEvent(UserEvents::FLAG_PLACED);
		hasFlag = true;
	}
}

//"Clear" a cell -- disable it, mark it visually as cleared and report the event to SDL's event queue
void MinesweeperCell::ClearCell() {
	if (isCleared) return;
	isCleared = true;
	SetIsDisabled(true);
	SetColor(Config::BUTTON_CLEARED_COLOR);
	ReportEvent(UserEvents::CELL_CLEARED);
}

//When a cell is cleared perform a cascading check on adjacent, clear cells and mark them as cleared.
void MinesweeperCell::HandleCellCleared(const SDL_UserEvent& E) {
	MinesweeperCell* Cell{ static_cast<MinesweeperCell*>(E.data1) };
	//If the cell has a bomb, don't clear it.
	if (Cell->hasBomb) return;
	//Clear all empty, adjacent cells
	if (isAdjacent(Cell) && Cell->AdjacentBombs == 0) {
		ClearCell();
	}
}

//Attempt to place a bomb on a cell. Returns false if the cell already has a bomb.
bool MinesweeperCell::PlaceBomb() {
	if (hasBomb) return false;
	hasBomb = true;
	ReportEvent(UserEvents::BOMB_PLACED);
	return true;
}

//Update the adjacent bomb info for a cell when a bomb is placed.
void MinesweeperCell::HandleBombPlaced(const SDL_UserEvent& E) {
	//We know that data1 will contain a MinesweeperCell when the event is triggered
	MinesweeperCell* Cell{ static_cast<MinesweeperCell*>(E.data1) };
	if (isAdjacent(Cell)) {
		++AdjacentBombs;
		//Update the adjacent bomb text since the amount of adjacent bombs has changed.
		Text.SetText(std::to_string(AdjacentBombs), Config::TEXT_COLORS[AdjacentBombs]);
	}
}

//Returns whether a given cell is adjacent to the method caller.
bool MinesweeperCell::isAdjacent(MinesweeperCell* Other) const {
	return !(Other == this)
		&& std::abs(GetRow() - Other->GetRow()) <= 1
		&& std::abs(GetCol() - Other->GetCol()) <= 1;
}

void MinesweeperCell::Reset() {
	isCleared = false;
	hasBomb = false;
	hasFlag = false;
	AdjacentBombs = 0;
	SetIsDisabled(false);
	SetColor(Config::BUTTON_COLOR);
}