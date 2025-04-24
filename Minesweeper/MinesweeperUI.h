#pragma once
#include "Globals.h"
#include "MinesweeperGrid.h"
#include "NewGameButton.h"
#include "FlagCounter.h"

class MinesweeperUI {
public:
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
        Button.Render(Surface);
        Counter.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E) {
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
    }

private:
    MinesweeperGrid Grid{
        Config::PADDING,
        Config::PADDING
    };

    NewGameButton Button{
        Config::PADDING,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        Config::WINDOW_WIDTH - Config::PADDING * 3 - Config::FLAG_COUNTER_WIDTH,
        Config::FOOTER_HEIGHT - Config::PADDING
    };
    FlagCounter Counter{
        Config::WINDOW_WIDTH - Config::PADDING - Config::FLAG_COUNTER_WIDTH,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        Config::FLAG_COUNTER_WIDTH,
        Config::FOOTER_HEIGHT - Config::PADDING
    };
};