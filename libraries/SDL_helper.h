#include <iostream>
#include <vector>
#include <ctime>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "glm/glm.hpp"
#include "debug.c"

#ifndef SCREENSHOT_PATH
	#define SCREENSHOT_PATH "screenshots"
#endif

using glm::vec3;


// Some useful color constants.
const vec3 BLACK = vec3(0.0f, 0.0f, 0.0f);
const vec3 GREY  = vec3(0.5f, 0.5f, 0.5f);
const vec3 WHITE = vec3(1.0f, 1.0f, 1.0f);

const vec3 RED	 = vec3(1.0f, 0.0f, 0.0f);
const vec3 GREEN = vec3(0.0f, 1.0f, 0.0f);
const vec3 BLUE  = vec3(0.0f, 0.0f, 1.0f);

const vec3 CYAN    = vec3(0.0f, 1.0f, 1.0f);
const vec3 YELLOW  = vec3(1.0f, 1.0f, 0.0f);
const vec3 MAGENTA = vec3(1.0f, 0.0f, 1.0f);


/// Map from float in range [0, 1] to uint8 in range [0, 255].
Uint8 MapFloatToUint8(float color)
{
	Assert(0.0f <= color && color <= 1.0039f, "Color value must be in range [0, 1], not %f.", color);
	return static_cast<Uint8>(color * 255.0f);
}

/// Map from floating-point vec3 of RGBA to a 32-bit RGBA value.
Uint32 ColorCode(const glm::vec3& color)
{
	return (MapFloatToUint8(1.0f)    << 24) +
		   (MapFloatToUint8(color.r) << 16) +
		   (MapFloatToUint8(color.g) << 8) +
		   (MapFloatToUint8(color.b));
}


struct Clock
{
public:
	Clock() : current_tick(SDL_GetTicks()), last_tick(current_tick) {}

	/// Returns the time, in seconds, since last call to `tick`.
	float tick()
	{
		this->last_tick    = this->current_tick;
		this->current_tick = SDL_GetTicks();

		unsigned delta = this->current_tick - this->last_tick;
		return delta / 1000.0f;
	}

private:
	unsigned current_tick;
	unsigned last_tick;
};




class Window
{
public:
	static Window Create(const std::string& name, int width, int height)
	{
		Assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0, "Couldn't initialize SDL. %s", SDL_GetError());

		unsigned window_flags   = 0;                       // https://wiki.libsdl.org/SDL_WindowFlags
		unsigned renderer_flags = SDL_RENDERER_SOFTWARE;   // https://wiki.libsdl.org/SDL_RendererFlags

		SDL_Window*   window   = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);
		SDL_Texture*  screen   = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

		Assert(window,   "Couldn't create window. %s",   SDL_GetError());
		Assert(renderer, "Couldn't create renderer. %s", SDL_GetError());
		Assert(screen,   "Couldn't create texture. %s",  SDL_GetError());

		int w, h;
		SDL_GetRendererOutputSize(renderer, &w, &h);
		Uint32* pixels = new Uint32[size_t(w) * size_t(h)];

		return { window, renderer, screen, pixels };
	}

	static void Destroy(Window* window) {
		delete[] window->pixels;
		SDL_DestroyTexture(window->screen);
		SDL_DestroyRenderer(window->renderer);
		SDL_DestroyWindow(window->handle);

		window = nullptr;
	}

	void set_pixel(int x, int y, const glm::vec3& color)
	{
		int width, height;
		SDL_GetRendererOutputSize(this->renderer, &width, &height);

		Assert(0 <= x && x < width,  "x must be between 0 and %i, got %i", width,  x);
		Assert(0 <= y && y < height, "y must be between 0 and %i, got %i", height, y);

		this->pixels[y * width + x] = ColorCode(color);
	}

	void fill(const glm::vec3& color)
	{
		Uint8 r = MapFloatToUint8(color.r);
		Uint8 g = MapFloatToUint8(color.g);
		Uint8 b = MapFloatToUint8(color.b);
		
		Assert(SDL_SetRenderDrawColor(this->renderer, r, g, b, 255) == 0, "Error: %s", SDL_GetError());
		Assert(SDL_RenderClear(this->renderer) == 0, "Error: %s", SDL_GetError());

		int width, height;
		SDL_GetRendererOutputSize(this->renderer, &width, &height);

		Uint32 color_code = ColorCode(color);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
				this->pixels[y * width + x] = color_code;

		Assert(SDL_UpdateTexture(this->screen, nullptr, this->pixels, width * sizeof(Uint32)) == 0, "Error: %s", SDL_GetError());
	}

	void update() 
	{
		int width, height;
		SDL_GetRendererOutputSize(this->renderer, &width, &height);

		Assert(SDL_UpdateTexture(this->screen, nullptr, &this->pixels[0], width * 4) == 0, "Error: %s", SDL_GetError());

		Assert(SDL_RenderCopy(this->renderer, this->screen, nullptr, nullptr) == 0, "Error: %s", SDL_GetError());
		SDL_RenderPresent(this->renderer);
	}

	void screenshot(const std::string& filename)
	{
		int width, height;
		SDL_GetRendererOutputSize(this->renderer, &width, &height);

		std::string full_path = SCREENSHOT_PATH + filename;

		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(this->pixels, width, height, 32, width * 4, 0, 0, 0, 0);
		Assert(SDL_SaveBMP(surface, full_path.c_str()) == 0, "Error: %s", SDL_GetError());
		SDL_FreeSurface(surface);
	}

	void screenshot()
	{
		using namespace std;

		time_t raw_time;
		tm*    time_info;
		char   buffer[80];

		time(&raw_time);
		time_info = localtime(&raw_time);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", time_info);
		string date_and_time(buffer);

		this->screenshot(date_and_time + ".bmp");
	}


private:
	Window(SDL_Window* handle, SDL_Renderer* renderer, SDL_Texture* screen, Uint32* pixels) 
		: handle(handle), renderer(renderer), screen(screen), pixels(pixels) {}

	SDL_Window*   handle;
	SDL_Renderer* renderer;
	SDL_Texture*  screen;
	Uint32*       pixels;
};




