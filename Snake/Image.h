#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Config.h"

class Image {
public:
    Image(const std::string& Path) {
        ImageSurface = IMG_Load(Path.c_str());
        CheckSDLError("Loading Image");
    }

    ~Image() {
        if (ImageSurface) {
            SDL_FreeSurface(ImageSurface);
        }
    }

    void Render(SDL_Surface* Surface, SDL_Rect* Rect) {
        SDL_BlitScaled(ImageSurface, nullptr, Surface, Rect);
    }

    // Prevent copying
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

private:
    SDL_Surface* ImageSurface;
};