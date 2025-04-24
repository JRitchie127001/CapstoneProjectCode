#define SDL_MAIN_HANDLED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Globals.h"
#include "Window.h"
#include "MinesweeperUI.h"


int main(int argc, char** argv) {
	//Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO);
#ifdef DEBUG
	Utils::CheckSDLError("SDL_Init");
#endif // DEBUG

	IMG_Init(IMG_INIT_PNG);
#ifdef DEBUG
	Utils::CheckSDLError("IMG_Init");
#endif

	TTF_Init();
#ifdef DEBUG
	Utils::CheckSDLError("TTF_Init");
#endif

	Engine::Window GameWindow;
	MinesweeperUI UI;

	SDL_Event Event;
	bool Exit{ false };
	
	while (!Exit) {
		while (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_QUIT) {
				Exit = true;
			}
			else { UI.HandleEvent(Event); }
		}
		GameWindow.Render();
		UI.Render(GameWindow.GetSurface());
		GameWindow.Update();
	}

	SDL_Quit();
	return 0;
}