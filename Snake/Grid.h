#pragma once
#include <vector>
#include "Cell.h"
#include "Config.h"
#include "Random.h"

class Grid {
public:
    //Fill the grid with cells on construction + include a reference for the image asset
    Grid(Assets& Assets) {
        using namespace Config;
        Cells.reserve(GRID_ROWS * GRID_COLUMNS);
        for (int R{ 0 }; R < GRID_ROWS; ++R) {
            for (int C{ 0 }; C < GRID_COLUMNS; ++C) {
                Cells.emplace_back(R, C, Assets);
            }
        }
    }
    void HandleEvent(SDL_Event& E) {
        for (auto& Cell : Cells) {
            Cell.HandleEvent(E);
        }

        if (E.type == UserEvents::APPLE_EATEN) {
            PlaceRandomApple();
        }
    }

    void Tick(Uint32 DeltaTime) {
        for (auto& Cell : Cells) {
            Cell.Tick(DeltaTime);
        }
    }

    void Render(SDL_Surface* Surface) {
        for (auto& Cell : Cells) {
            Cell.Render(Surface);
        }
    }

    
private:
	std::vector<Cell> Cells;

    void PlaceRandomApple() {
        using Random::Int;
        while (true) {
#pragma warning( push )
#pragma warning( disable : 4267) //Unless our grid dimensions are bigger than the target platform's size_t the warning can be safely ignored...
            size_t RandomIndex{ static_cast<size_t>(Random::Int(0, Cells.size() - 1)) };
#pragma warning( pop ) 
            if (Cells[RandomIndex].PlaceApple()) {
                break;
            }
        }
    }
};