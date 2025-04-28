#pragma once

#include "Random.h"
#include <vector>
#include "Config.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "GameBoard.h"
#include <algorithm>


/// <summary>
/// Generates the code to be guessed and validates guesses.
/// </summary>
class GameManager {
public:
	void HandleEvent(const SDL_Event& E) {
		//User Guess
		if (E.type == UserEvents::GUESS_MADE) {
			//If the user clicks the guess too early, return
			if (std::find(Guess.begin(), Guess.end(), -1) != Guess.end()){
#ifdef DEBUG
				std::cout << "Invalid guess. Guess array: ";
				for (auto& e : Guess) {
					std::cout << e << ", ";
				}
				std::cout << '\n';
#endif // DEBUG
				return;
			}
			else {
#ifdef DEBUG
				std::cout << "Guess array: ";
				for (auto& e : Guess) {
					std::cout << e << ", ";
				}
				std::cout << '\n';
#endif // DEBUG
				Result = Validate(Guess);
				ReportEvent(UserEvents::GUESS_VALIDATED);
				
				//If the game is over, push the GAME LOST event
				if (Round == Config::ROUNDS) {
					SDL_Event Event{ UserEvents::GAME_LOST };
					SDL_PushEvent(&Event);
				}
				//Likewise with if the user won
				else if (Result[0] == Config::GRID_COLUMNS) {
					SDL_Event Event{ UserEvents::GAME_WON };
					SDL_PushEvent(&Event);
				}
				//Otherwise go to the next round.
				else {
					SDL_Event Event{ UserEvents::NEXT_ROUND };
					SDL_PushEvent(&Event);
				}
			}
		}
		//Win
		else if (E.type == UserEvents::GAME_WON) {
#ifdef DEBUG
			std::cout << "Game Won";
#endif // DEBUG
		}
		//Loss
		else if (E.type == UserEvents::GAME_LOST) {
#ifdef DEBUG
			std::cout << "Game Lost";
#endif // DEBUG
		}
	}

	void GenerateCode() {
		Code.resize(Config::GRID_COLUMNS);
		Guess.resize(Config::GRID_COLUMNS);
		for (int i = Config::GRID_COLUMNS - 1; i >= 0; --i) {
			Code[i] = Random::Int(0, Config::COLORS.size() - 1);
#ifdef DEBUG
			Code = { 0, 1, 1, 2 };
			std::cout << Code[i];
#endif // DEBUG
		}
	}

	std::vector<int> Validate(std::vector<int> Guess) {
		int Exact{ 0 };
		int Close{ 0 };
		//Find how many colors were correct as well as positioned correctly
		for (int i = Config::GRID_COLUMNS - 1; i >= 0; --i) {
			//If it matches the position AND color, add an exact peg
			if (Guess[i] == Code[i]) {
				++Exact;
			}
			Close = NonExactMatches(Guess, Code);
		}
#ifdef DEBUG
		std::cout << "Exact: " << Exact << " | Close: " << Close;
#endif // DEBUG
		//Empty the guess array for the next round.
		EmptyGuess();
		return { Exact, Close };
	}

	//Gets the appropriate index in the guess array with a matching color.
	void SetGuess(int index, int color) {
		Guess[index-1] = color;
	}

	//Gets the last guess result.
	std::vector<int> GetResult() {
		return Result;
	}

	//Resets the game state to the beginning.
	void Reset() {
		GenerateCode();
		Round = 1;
		Guess = { -1, -1, -1, -1 };
	}

	//Increments the round and returns the new round
	int NextRound() { ++Round; return Round; }

	void ReportEvent(uint32_t EventType) {
		SDL_Event event{ EventType };
		event.user.data1 = this;
		SDL_PushEvent(&event);
	}

private:
	
	std::vector<int> Result{ 0, 0 };
	std::vector<int> Code;
	std::vector<int> Guess {-1, -1, -1, -1};
	int Round{ 1 };
	void EmptyGuess() { Guess = { -1, -1, -1, -1 }; }

	//Finds the number of non-exact (same number, different index) match in two equally sized arrays.
	int NonExactMatches(std::vector<int> A, std::vector<int> B) {
		int Matches{ 0 };
		for (int i{ 0 }; i < A.size(); ++i) {
			if (std::find(A.begin(), A.end(), B[i]) != A.end() && (A[i] != B[i]))
			{
				++Matches;
			}
		}
		return Matches;
	}
};