#pragma once
#include <SDL2/SDL.h>
#include "Config.h"

class Window {
public:
    Window() {
        SDLWindow = SDL_CreateWindow(
            Config::GAME_NAME.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT, 0
        );

        CheckSDLError("Creating Window");
    }

    ~Window() {
        if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_DestroyWindow(SDLWindow);
        }
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void Render() {
        SDL_FillRect(
            GetSurface(), nullptr,
            SDL_MapRGB(GetSurface()->format,
                Config::BACKGROUND_COLOR.r,
                Config::BACKGROUND_COLOR.g,
                Config::BACKGROUND_COLOR.b));
    }

    void Update() {
        SDL_UpdateWindowSurface(SDLWindow);
    }

    SDL_Surface* GetSurface() {
        return SDL_GetWindowSurface(SDLWindow);
    }

private:
    SDL_Window* SDLWindow;
};