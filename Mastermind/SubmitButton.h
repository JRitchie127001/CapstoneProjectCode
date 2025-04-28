#pragma once
#include <SDL2/SDL.h>
#include "Text.h"
#include "GameManager.h"

/// <summary>
/// Handles submitting guesses and restarting a won/lost game.
/// </summary>
class SubmitButton {
public:
    void Render(SDL_Surface* Surface) {
        SDL_FillRect(Surface, &ButtonRect,
            SDL_MapRGB(
                Surface->format,
                CurrentColor.r,
                CurrentColor.g,
                CurrentColor.b
            )
        );
        Text.Render(Surface, &TextRect);
    }

    void HandleEvent(const SDL_Event& E) {
        using namespace UserEvents;
        using namespace Config;
        if (E.type == SDL_MOUSEBUTTONDOWN) {
            HandleClick(E.button);
        }
        else if (E.type == GAME_WON) {
            Text.SetText("You win!");
            GameOver = true;
        }
        else if (E.type == GAME_LOST) {
            Text.SetText("You lose...");
            GameOver = true;
        }
    }
private:
    SDL_Color CurrentColor{ Config::BUTTON_COLOR };
    Text Text{ "SUBMIT", 20 };
    SDL_Rect ButtonRect{
        Config::WINDOW_WIDTH / 3,
        Config::GRID_HEIGHT,
        Config::GRID_WIDTH - (Config::PADDING * 3),
        Config::GRID_HEIGHT/Config::GRID_ROWS - Config::PADDING 
    };
    SDL_Rect TextRect{
        ButtonRect.x + Config::PADDING * 5,
        ButtonRect.y + Config::PADDING * 3,
        0, 0
    };
    bool GameOver = false;

    //Check if the click was in the button bounds.
    void HandleClick(const SDL_MouseButtonEvent& E) {
        using namespace UserEvents;
        if (
            E.x >= ButtonRect.x &&
            E.x <= ButtonRect.x + ButtonRect.w &&
            E.y >= ButtonRect.y &&
            E.y <= ButtonRect.y + ButtonRect.h
            ) {
            if (!GameOver) {
                SDL_Event Guess{ UserEvents::GUESS_MADE };
                SDL_PushEvent(&Guess);
            }
            else {
                Text.SetText("Submit");
                GameOver = false;
                SDL_Event Restart{ UserEvents::NEW_GAME };
                SDL_PushEvent(&Restart);
            }
        }
    }
};