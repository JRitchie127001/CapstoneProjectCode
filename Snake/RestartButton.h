#pragma once
#include <SDL2/SDL.h>
#include "Text.h"

class RestartButton {
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

    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        using namespace Config;
        //Handle click events
        if (E.type == SDL_MOUSEBUTTONDOWN) {
            HandleClick(E.button);
        }
        //Highlight the button when the game is over
        else if (E.type == GAME_LOST || E.type == GAME_WON) {
            CurrentColor = BUTTON_HIGHLIGHT_COLOR;
        }
        //Change the color to normal on restart.
        else if (E.type == RESTART_GAME) {
            CurrentColor = BUTTON_COLOR;
        }
    }
private:
    SDL_Color CurrentColor{ Config::BUTTON_COLOR };
    Text Text{ "RESTART", 20 };
    SDL_Rect ButtonRect{
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
    };
    SDL_Rect TextRect{
        ButtonRect.x + Config::PADDING * 5,
        ButtonRect.y + Config::PADDING * 3, 
        0, 0
    };

    //Check if the click was in the button bounds.
    void HandleClick(SDL_MouseButtonEvent& E) {
        using namespace UserEvents;
        if (
            E.x >= ButtonRect.x &&
            E.x <= ButtonRect.x + ButtonRect.w &&
            E.y >= ButtonRect.y &&
            E.y <= ButtonRect.y + ButtonRect.h
            ) {
            SDL_Event RestartEvent{ RESTART_GAME };
            SDL_PushEvent(&RestartEvent);
        }
    }
};