#pragma once
#include "Globals.h"
#include "Rectangle.h"

namespace Engine {
	class Button : public Rectangle {
	public:
		Button(int x, int y, int w, int h) :
			Rectangle{ x, y, w ,h } {
			SetColor(Config::BUTTON_COLOR);
		}
		virtual void HandleEvent(const SDL_Event& E) {
			if (isDisabled) return;
			if (E.type == SDL_MOUSEMOTION) {
				HandleMouseMotion(E.motion);
			}
			else if (E.type == SDL_MOUSEBUTTONDOWN) {
				if (IsWithinBounds(E.button.x, E.button.y)) {
					E.button.button == SDL_BUTTON_LEFT
						? HandleLeftClick() : HandleRightClick();
				}
			}
		}

		void SetIsDisabled(bool NewValue) {
			isDisabled = NewValue;
		}

	protected:
		virtual void HandleLeftClick() {}
		virtual void HandleRightClick() {}
		virtual void HandleMouseMotion(const SDL_MouseMotionEvent& E) {
			if (IsWithinBounds(E.x, E.y)) {
				SetColor(Config::BUTTON_HOVER_COLOR);
			}
			else {
				SetColor(Config::BUTTON_COLOR);
			}
		}

	private:
		bool isDisabled{ false };
	};
}