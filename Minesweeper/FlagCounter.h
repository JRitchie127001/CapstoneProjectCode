#pragma once
#include <string>

#include "Globals.h"

#include "Rectangle.h";
#include "Text.h"
#include "Image.h"

class FlagCounter : public Engine::Rectangle {
public:
	FlagCounter(int x, int y, int w, int h) :
		Rectangle{ x,y,w,h, Config::FLAG_COUNTER_COLOR },
		Image{ x,y,
		Config::FOOTER_HEIGHT - Config::PADDING,
		Config::FOOTER_HEIGHT - Config::PADDING,
		Config::FLAG_IMAGE,
		24
		},
		Text{
		x + Config::FOOTER_HEIGHT, y,
		w - Config::FOOTER_HEIGHT - 24, h,
		std::to_string(Config::BOMB_COUNT),
			{255,255,255,255}, 20 } {}

	//Overriding the base render in order to show the text and flag image.
	void Render(SDL_Surface* Surface) override {
		Rectangle::Render(Surface);
		Text.Render(Surface);
		Image.Render(Surface);
	}

	void HandleEvent(const SDL_Event& E) {
		//Flag Placed
		if (E.type == UserEvents::FLAG_PLACED) {
			--FlagsAvailable;
		}
		//Flag Cleared
		else if (E.type == UserEvents::FLAG_CLEARED) {
			++FlagsAvailable;
		}
		//Game Won
		else if (E.type == UserEvents::GAME_WON) {
			FlagsAvailable = 0;
		}
		//New Game
		else if (E.type == UserEvents::NEW_GAME) {
			FlagsAvailable = Config::BOMB_COUNT;
		}
		else {
			return;
		}

		Text.SetText(std::to_string(FlagsAvailable));
	}
private:
	Engine::Image Image;
	Engine::Text Text;

	int FlagsAvailable{ Config::BOMB_COUNT };
};