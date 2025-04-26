#pragma once
#include <SDL2/SDL.h>
#include "Assets.h"
#include "SnakeData.h" 
#include "Config.h"

enum CellState { Snake, Apple, Empty };

class Cell {
public:
    Cell(int Row, int Column, Assets& Assets) :
        Row(Row),
        Column(Column),
        Assets{ Assets },
        BackgroundRect{
            Column * Config::CELL_SIZE + Config::PADDING,
            Row * Config::CELL_SIZE + Config::PADDING,
            Config::CELL_SIZE,
            Config::CELL_SIZE },
        BackgroundColor{(Row + Column) % 2 == 0 ? Config::CELL_COLOR_A : Config::CELL_COLOR_B }
    {
        Initialize();
    }

    //Handles all game logic with regards to the snake / cells
    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        //Handle the snake advancing
        if (E.type == ADVANCE) {
            Advance(E.user);
        }
        //Increment the duration of the snake when it eats an apple -- this effectively makes it longer by one segment for cells it was already in.
        else if (E.type == APPLE_EATEN) {
            if (CellState == Snake) {
                ++SnakeDuration;
            }
        }
        //Change the snake color if the player has won or lost.
        else if (E.type == GAME_LOST) {
            SnakeColor = Config::SNAKE_LOST_COLOR;
        }
        else if (E.type == GAME_WON) {
            SnakeColor = Config::SNAKE_VICTORY_COLOR;
        }
        //Reset the game when the restart event is triggered.
        else if (E.type == RESTART_GAME) {
            Initialize();
        }
    }

    //Tick Logic
    void Tick(Uint32 DeltaTime) {
        if (CellState == Snake && FillPercent < 1) {
            GrowHead(DeltaTime);
        }
        else if (CellState != Snake && FillPercent > 0) {
            ShrinkTail(DeltaTime);
        }
    }

    //Render logic
    void Render(SDL_Surface* Surface) {
        SDL_FillRect(Surface, &BackgroundRect,
            SDL_MapRGB(
                Surface->format,
                BackgroundColor.r,
                BackgroundColor.g,
                BackgroundColor.b
            )
        );

        //Render the appropriate image for any objects on the cell

        //Apple
        if (CellState == Apple) {
            Assets.Apple.Render(Surface, &BackgroundRect);
        }

        
        //Snake
        else if (FillPercent > 0) {
            SDL_FillRect(Surface, &SnakeRect,
                SDL_MapRGB(
                    Surface->format,
                    SnakeColor.r,
                    SnakeColor.g,
                    SnakeColor.b
                )
            );
        }
    }

    bool PlaceApple() {
        if (CellState != Empty) return false;

        CellState = Apple;
        return true;
    }

private:
    //Set or reset the game state back to the initial values
    void Initialize() {
        CellState = Empty;
        SnakeDuration = 0;
        SnakeColor = Config::SNAKE_COLOR;
        SnakeRect = BackgroundRect;
        FillPercent = 0.0;
        FillDirection = Right;

        //Find the middle row of our grid and put the snake on it with an apple to the right.
        int MiddleRow{ Config::GRID_ROWS / 2 };
        if (Row == MiddleRow && Column == 2) {
            CellState = Snake;
            SnakeDuration = 1;
            FillPercent = 1.0;
        }
        else if (Row == MiddleRow && Column == 3) {
            CellState = Snake;
            SnakeDuration = 2;
            FillPercent = 1.0;
        }
        else if (Row == MiddleRow && Column == 11) {
            CellState = Apple;
        }
    }

    void Advance(SDL_UserEvent& E) {
        SnakeData* Data{ static_cast<SnakeData*>(E.data1) };
        bool isThisCell{Data->HeadRow == Row && Data->HeadCol == Column};

        //If the snake is in the cell handle game logic
        if (isThisCell) {
            //Eat the apple if the snake enters the cell
            if (CellState == Apple) {
                SDL_Event Event{ UserEvents::APPLE_EATEN };
                SDL_PushEvent(&Event);
            }
            //Send the GAME_LOST event if the snake collides with itself.
            if (CellState == Snake) {
                SDL_Event Event{ UserEvents::GAME_LOST };
                SDL_PushEvent(&Event);
                return;
            }
            CellState = Snake;
            //Set the duration to the length of the snake when the cell is entered.
            SnakeDuration = Data->Length;
            FillDirection = Data->Direction;
            FillPercent = 0;
        }
        //Decrement the snake duration as the snake moves through the cell each game tick.
        else if (CellState == Snake) {
            //Tail animation logic
            if (SnakeDuration == Data->Length) {
                FillDirection = Data->Direction;
            }
            --SnakeDuration;
            if (SnakeDuration == 0) {
                CellState = Empty;
            }
        }
    }

    //Animates the snake's head moving into/through a cell
    void GrowHead(float DeltaTime) {
        using namespace Config;
        FillPercent += DeltaTime / ADVANCE_INTERVAL;
        if (FillPercent > 1) FillPercent = 1;

        //Fill the cell as the snake moves through it
        SnakeRect = BackgroundRect;
        if (FillDirection == Right) {
            SnakeRect.w = CELL_SIZE * FillPercent;
        }
        else if (FillDirection == Down) {
            SnakeRect.h = CELL_SIZE * FillPercent;
        }
        else if (FillDirection == Left) {
            SnakeRect.x = BackgroundRect.x +
                CELL_SIZE * (1 - FillPercent);
        }
        else if (FillDirection == Up) {
            SnakeRect.y = BackgroundRect.y +
                CELL_SIZE * (1 - FillPercent);
        }
    }

    //Animates the snake's tail leaving a cell.
    void ShrinkTail(float DeltaTime) {
        using namespace Config;

        //Empty the cell as the snake leaves it.
        FillPercent -= DeltaTime / ADVANCE_INTERVAL;
        if (FillPercent < 0) FillPercent = 0;

        if (FillDirection == Right) {
            SnakeRect.x = BackgroundRect.x +
                CELL_SIZE * (1 - FillPercent);
        }
        else if (FillDirection == Left) {
            SnakeRect.w = CELL_SIZE * FillPercent;
        }
        else if (FillDirection == Up) {
            SnakeRect.h = CELL_SIZE * FillPercent;
        }
        else if (FillDirection == Down) {
            SnakeRect.y = BackgroundRect.y +
                CELL_SIZE * (1 - FillPercent);
        }
    }

    //Coords
    int Row;
    int Column;
    //Game logic
    CellState CellState;
    int SnakeDuration; //The number of game ticks the snake will be occupying the cell. The value is equal to its length when its head has entered the cell.
    SDL_Color SnakeColor{ Config::SNAKE_COLOR };
    //SDL
    SDL_Rect BackgroundRect;
    SDL_Color BackgroundColor;
    Assets& Assets;
    //Animation
    SDL_Rect SnakeRect;
    float FillPercent{ 0 };
    MovementDirection FillDirection{ Right };
};