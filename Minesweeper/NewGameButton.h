#pragma once
#include "Globals.h"

#include "Button.h"
#include "Text.h"

class NewGameButton : public Engine::Button {
public:
	NewGameButton(int x, int y, int w, int h) : Button(x, y, w, h), Text{ x,y,w,h, "New Game", {}, 20 } {}

	//We override the base render method to display the text.
	void Render(SDL_Surface* Surface) override {
		Button::Render(Surface);
		Text.Render(Surface);
	}

	void HandleLeftClick() override {
		SDL_Event E{ UserEvents::NEW_GAME };
		SDL_PushEvent(&E);
	}
private:
	Engine::Text Text;
};