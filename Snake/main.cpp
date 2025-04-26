#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Window.h"
#include "GameUI.h"
#include "GameManager.h"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    CheckSDLError("Initializing SDL");

    IMG_Init(IMG_INIT_PNG);
    CheckSDLError("Initializing SDL_image");

    TTF_Init();
    CheckSDLError("Initializing SDL_ttf");

    Window GameWindow{};
    GameUI UI{};
    GameManager Manager;

    Uint32 PreviousTick{ SDL_GetTicks() };
    Uint32 CurrentTick;
    Uint32 DeltaTime;

    SDL_Event Event;
    while (true) {
        CurrentTick = SDL_GetTicks();
        DeltaTime = CurrentTick - PreviousTick;

        //Events
        while (SDL_PollEvent(&Event)) {
            UI.HandleEvent(Event);
            Manager.HandleEvent(Event);
            if (Event.type == SDL_QUIT) {
                SDL_Quit();
                IMG_Quit();
                return 0;
            }
        }

        //Tick
        UI.Tick(DeltaTime);
        Manager.Tick(DeltaTime);

        //Rendering
        GameWindow.Render();
        UI.Render(GameWindow.GetSurface());

        //Swap
        GameWindow.Update();

        PreviousTick = CurrentTick;
    }

    return 0;
}