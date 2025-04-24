#pragma once
#include <SDL2/SDL_image.h>
#include <string>

namespace Engine {
	class Image {
	public:
		Image(int x, int y, int w, int h,
			const std::string& Filename,
			int Padding = 12) : 
			Destination { x + Padding/2, y + Padding/2, w-Padding, h-Padding}
		{
			ImageSurface = IMG_Load(Filename.c_str());
#ifdef DEBUG
			Utils::CheckSDLError("IMG_Load");
#endif // DEBUG
		}

		void Render(SDL_Surface* Surface) {
			SDL_BlitScaled(ImageSurface, nullptr, Surface, &Destination);
		}

		~Image() {
			if (ImageSurface) {
				SDL_FreeSurface(ImageSurface);
			}
		}

		Image(const Image&){}

	private:
		SDL_Surface* ImageSurface{ nullptr };
		SDL_Rect Destination{ 0,0,0,0 };
	};
}
