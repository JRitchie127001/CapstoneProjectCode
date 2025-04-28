#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MastermindUI.h"
#include "Window.h"
#include "GameManager.h"

/// <summary>
/// Event loop for Mastermind game.
/// </summary>
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();

    Window GameWindow{};
    MastermindUI UI{};

    SDL_Event Event;
    while (true) {
        //Events
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_QUIT) {
                SDL_Quit();
                IMG_Quit();
                return 0;
            }
            else { UI.HandleEvent(Event); }
        }
        //Rendering
        GameWindow.Render();
        UI.Render(GameWindow.GetSurface());

        //Swap
        GameWindow.Update();
    }
    return 0;
}