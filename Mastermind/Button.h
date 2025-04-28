#pragma once
#include "Config.h"
#include "Rectangle.h"

/// <summary>
/// Button class that can recieve and handle left/right click events.
/// </summary>
namespace Engine {
	class Button : public Rectangle {
	public:
		Button(int x, int y, int w, int h) :
			Rectangle{ x, y, w ,h } {
		}
		virtual void HandleEvent(const SDL_Event& E) {
			if (isDisabled) return;
			if (E.type == SDL_MOUSEBUTTONDOWN) {
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
	private:
		bool isDisabled{ false };
	};
}