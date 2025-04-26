#pragma once
#include <SDL2/SDL.h>
#include "Assets.h"
#include "Grid.h"
#include "RestartButton.h"
#include "ScoreCounter.h"

class GameUI {
public:
	GameUI() : Grid{ Assets }, ScoreCounter{ Assets } {}

	void HandleEvent(SDL_Event& E) {
		Grid.HandleEvent(E);
		RestartButton.HandleEvent(E);
		ScoreCounter.HandleEvent(E);
	}

	void Tick(Uint32 DeltaTime) {
		Grid.Tick(DeltaTime);
	}

	void Render(SDL_Surface* Surface) {
		Grid.Render(Surface);
		RestartButton.Render(Surface);
		ScoreCounter.Render(Surface);
	}

private:
	Grid Grid;
	Assets Assets;
	RestartButton RestartButton;
	ScoreCounter ScoreCounter;
};