#pragma once
#include <SDL2/SDL.h>
#include "SnakeData.h"
#include "Config.h"

class GameManager {
public:
	void HandleEvent(SDL_Event& E) {
		using namespace UserEvents;
		using namespace Config;
		//Key Events
		if (E.type == SDL_KEYDOWN) {
			//Don't bother handling key events while in the game loss state.
			if (IsGameOver) return;
			HandleKeyEvent(E.key);
		}
		//Apple Eaten
		else if (E.type == APPLE_EATEN) {
			++Snake.Length;
			//If the snake has reached the max length we push the win state onto the queue.
			if (Snake.Length >= MAX_LENGTH) {
				SDL_Event Event{ GAME_WON };
				SDL_PushEvent(&Event);
			}
		}
		//Handle the game ending (win and loss)
		else if (E.type == GAME_LOST || E.type == GAME_WON) {
			IsGameOver = true;
		}
		//Restart
		else if (E.type == RESTART_GAME) {
			RestartGame();
		}
	}
	void Tick(Uint32 DeltaTime) {
		//If the game is paused of over, skip the tick logic.
		if (IsPaused || IsGameOver) return;
		//Tick if we've waited long enough for the advance interval set in the config
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= Config::ADVANCE_INTERVAL) {
			ElapsedTime = 0;
			UpdateSnake();
		}
	}
private:
	bool IsGameOver{ false };
	bool IsPaused{ true };
	Uint32 ElapsedTime{ 0 };
	MovementDirection NextDirection{ Right };

	//Starting position of the snake.
	SnakeData Snake{
		.HeadRow = Config::GRID_ROWS / 2,
		.HeadCol = 3,
		.Length = 2,
		.Direction = Right
	};

	//Controls
	void HandleKeyEvent(SDL_KeyboardEvent& E) {
		switch (E.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			if (Snake.Direction != Down) {
				NextDirection = Up;
			}
			break;
		case SDLK_DOWN:
		case SDLK_s:
			if (Snake.Direction != Up) {
				NextDirection = Down;
			}
			break;
		case SDLK_LEFT:
		case SDLK_a:
			if (Snake.Direction != Right) {
				NextDirection = Left;
			}
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			//Let the user press "RIGHT / D" to begin the game
			if (IsPaused) {
				IsPaused = false;
				NextDirection = Right;
				UpdateSnake();
			}
			else if (Snake.Direction != Left) {
				NextDirection = Right;
			} 
			break;
		}
	}

	//Move the snake based on its heading
	void UpdateSnake() {
		Snake.Direction = NextDirection;
		switch (NextDirection) {
		case Up:
			Snake.HeadRow--;
			break;
		case Down:
			Snake.HeadRow++;
			break;
		case Left:
			Snake.HeadCol--;
			break;
		case Right:
			Snake.HeadCol++;
			break;
		}
		//Check if the snake is moving into one of the boundary walls.
		if (
			Snake.HeadRow < 0 ||
			Snake.HeadRow >= Config::GRID_ROWS ||
			Snake.HeadCol < 0 ||
			Snake.HeadCol >= Config::GRID_COLUMNS
			) {
			SDL_Event Event{ UserEvents::GAME_LOST };
			SDL_PushEvent(&Event);
		}
		else {
			//Advance if we are in-bounds
			SDL_Event Event{ UserEvents::ADVANCE };
			Event.user.data1 = &Snake;
			SDL_PushEvent(&Event);
		}
	}

	void RestartGame() {
		IsGameOver = false;
		IsPaused = true;
		ElapsedTime = 0;
		Snake = { Config::GRID_ROWS / 2, 3, 2, Right };
		NextDirection = Right;
	}
};