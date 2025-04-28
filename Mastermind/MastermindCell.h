#pragma once
#include "SDL2/SDL.h"
#include "Rectangle.h"
#include "Button.h"


/// <summary>
/// Handles the game logic for the cells used to guess the code. 
/// </summary>
class MastermindCell : public Engine::Button {
public:
	MastermindCell(int X, int Y, int W, int H, int Row, int Col);

	void HandleEvent(const SDL_Event& E) override;
	void Reset();

	[[nodiscard]]
	int GetRow() const { return Row; }

	[[nodiscard]]
	int GetCol() const { return Col; }

	[[nodiscard]]
	int GetColor() const { return Color; }

	void SetActive(bool NewState) { Active = NewState; }

protected:
	void HandleLeftClick() override;
	void HandleRightClick() override;

private:
	//Coords
	int Row;
	int Col;
	//Events
	void ReportEvent(uint32_t EventType);
	
	//Game Logic
	int Color{ -1 };
	bool Active { false };
};