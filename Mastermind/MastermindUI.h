#pragma once
#include "Config.h"
#include "GameBoard.h"
#include "SubmitButton.h"
#include "ClueDisplay.h"

/// <summary>
/// UI Manager for Mastermind game.
/// </summary>
class MastermindUI {
public:
    void Render(SDL_Surface* Surface) {
        Board.Render(Surface);
        Submit.Render(Surface);
        Clue.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E) { 
        Board.HandleEvent(E);
        Submit.HandleEvent(E);
        Clue.HandleEvent(E);
    }
private:
    GameBoard Board{ (Config::WINDOW_WIDTH/3), Config::PADDING};
    SubmitButton Submit;
    ClueDisplay Clue;
};