#pragma once
#include <SDL2/SDL_ttf.h>
#include "Globals.h"

namespace Engine {
    class Text {
    public:
        Text(
            int x, int y, int w, int h,
            const std::string& Content,
            SDL_Color Color = { 0, 0, 0, 255 },
            int FontSize = 30
        ) : DestinationRect{ x, y, w, h },
            Color{ Color }
        {
            Font = TTF_OpenFont(
                Config::FONT.c_str(), FontSize);
#ifdef DEBUG
            Utils::CheckSDLError("TTF_OpenFont");
#endif
            SetText(Content);
        }

        void SetText(const std::string& Text) {
            SetText(Text, Color);
        }

        void SetText(const std::string& Text,
            SDL_Color NewColor) {
            if (TextSurface) {
                SDL_FreeSurface(TextSurface);
            }
            Color = NewColor;

            TextSurface = TTF_RenderUTF8_Blended(
                Font, Text.c_str(), Color
            );

            auto [x, y, w, h] = DestinationRect;
            // Horizontal centering
            const int WidthDifference{
              w - TextSurface->w };
            const int LeftOffset{ WidthDifference / 2 };

            // Vertical centering
            const int HeightDifference{
              h - TextSurface->h };
            const int TopOffset{ HeightDifference / 2 };

            TextPosition = {
              x + LeftOffset, y + TopOffset, w, h
            };
        }

        void Render(SDL_Surface* Surface) {
            SDL_BlitSurface(
                TextSurface, nullptr,
                Surface, &TextPosition
            );
        }

        ~Text() {
            if (Font) { TTF_CloseFont(Font); }
            if (TextSurface) {
                SDL_FreeSurface(TextSurface);
            }
        }

    private:
        SDL_Surface* TextSurface{ nullptr };
        TTF_Font* Font{ nullptr };
        SDL_Rect DestinationRect{ 0, 0, 0, 0 };
        SDL_Rect TextPosition{ 0, 0, 0, 0 };
        SDL_Color Color{ 0, 0, 0, 255 };
    };
}