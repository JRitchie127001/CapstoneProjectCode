#pragma once
#include <iostream>
#include "MastermindCell.h"
#include "Config.h"

/// <summary>
/// Create a Mastermind cell with x,y,w,h dimensions + row & column data.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="Row"></param>
/// <param name="Col"></param>
MastermindCell::MastermindCell(int x, int y, int w, int h, int Row, int Col) :
	Button{ x, y, w, h }, Row{ Row }, Col{ Col } { }

//Event Handlers
void MastermindCell::HandleEvent(const SDL_Event& E) {
	Button::HandleEvent(E);
}

//Report Event
void MastermindCell::ReportEvent(uint32_t EventType) {
	SDL_Event event{ EventType };
	event.user.data1 = this;
	SDL_PushEvent(&event);
}

//Go foward one colow
void MastermindCell::HandleLeftClick() {
	if (Active) {
		++Color;
		//Wrap the color around if it reaches the end
		if (Color > Config::COLORS.size() - 1) {
			Color = 1;
		}
		SetColor(Config::COLORS[Color]);
		ReportEvent(UserEvents::COLOR_CHANGED);
	}
}

//Go back one color.
void MastermindCell::HandleRightClick() {
	if (Active) {
		--Color;
		//Wrap the color around if it reaches the end
		if (Color < 0) {
			Color = Config::COLORS.size() - 1;
		}
		SetColor(Config::COLORS[Color]);
		ReportEvent(UserEvents::COLOR_CHANGED);
	}
}

//Set the cell to inactive, reset its color tracker and render color.
void MastermindCell::Reset() {
	SetActive(false);
	Color = -1;
	SetColor(SDL_Color(0, 0, 0, 0));
}