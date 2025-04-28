#pragma once
#include <SDL2/SDL.h>

/// <summary>
/// Creates a rectangle that has x,y,w,h dimensions and Color color. 
/// Capable of tracking if the mouse is in bounds with IsWithinBounds
/// </summary>
namespace Engine {
    class Rectangle {
    public:
        Rectangle(
            int x, int y, int w, int h,
            SDL_Color Color = { 0, 0, 0, 255 })
            : Rect{ x, y, w, h }, Color{ Color } {}

        virtual void Render(SDL_Surface* Surface) {
            SDL_FillRect(
                Surface, &Rect, SDL_MapRGB(
                    Surface->format, Color.r, Color.g,
                    Color.b
                )
            );
        }

        void SetColor(SDL_Color C) { Color = C; }

        SDL_Color GetColor() { return Color; }

        bool IsWithinBounds(int x, int y) const {
            // Too far left
            if (x < Rect.x) return false;
            // Too far right
            if (x > Rect.x + Rect.w) return false;
            // Too high
            if (y < Rect.y) return false;
            // Too low
            if (y > Rect.y + Rect.h) return false;
            // Within bounds
            return true;
        }

        SDL_Rect* GetRect() { return &Rect; }

        virtual ~Rectangle() = default;

    private:
        SDL_Rect Rect{ 0, 0, 0, 0 };
        SDL_Color Color{ 0, 0, 0, 0 };
    };
}