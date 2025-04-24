#pragma once
#include "Button.h"
#include "Image.h"
#include "Text.h"
class MinesweeperCell : public Engine::Button {
public:
	MinesweeperCell(int X, int Y, int W, int H, int Row, int Col);

	void HandleEvent(const SDL_Event& E) override;
	void Render(SDL_Surface* Surface) override;
	void Reset();
	bool PlaceBomb();

	[[nodiscard]]
	int GetRow() const { return Row; }

	[[nodiscard]]
	int GetCol() const { return Col; }

	[[nodiscard]]
	bool GetHasBomb() const { return hasBomb; }

protected:
	void HandleLeftClick() override;
	void HandleRightClick() override;

private:
	//Assets
	Engine::Image BombImage;
	Engine::Image FlagImage;
	Engine::Text Text;
	//Events
	void ReportEvent(uint32_t EventType);
	void HandleBombPlaced(const SDL_UserEvent& E);
	void ClearCell();
	void HandleCellCleared(const SDL_UserEvent& E);
	//Game Logic
	bool isAdjacent(MinesweeperCell* Other) const;
	bool isCleared{ false };
	bool hasBomb{ false };
	bool hasFlag{ false };
	int AdjacentBombs{ 0 };
	//Coords
	int Row;
	int Col;
};