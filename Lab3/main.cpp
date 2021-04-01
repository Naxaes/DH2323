#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "SDL_helper.h"
#include "TestModel.h"


using std::vector;

using glm::vec3;
using glm::mat3;
using glm::ivec2;


// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH  = 500;
const int SCREEN_HEIGHT = 500;


// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw(Window& window, const vector<Triangle>& triangles);
void Update(float dt);


int main(int argc, char* argv[])
{
	vector<Triangle> triangles = LoadTestModel();
	Window window = Window::Create("Lab1", SCREEN_WIDTH, SCREEN_HEIGHT);
	Clock  clock  = Clock();

	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		float dt = clock.tick();
		Update(dt);
		Draw(window, triangles);

		// NOTE: The pixels are not shown on the screen 
		// until we update the window with this method.
		window.update();
	}

	window.screenshot();

	Window::Destroy(&window);
	return 0;
}

void Update(float dt)
{
	std::cout << "Render time: " << dt << " s." << std::endl;

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	if (keystate[SDL_SCANCODE_UP])     { std::cout << "Pressing UP"		<< std::endl; }
	if (keystate[SDL_SCANCODE_DOWN])   { std::cout << "Pressing DOWN"	<< std::endl; }
	if (keystate[SDL_SCANCODE_RIGHT])  { std::cout << "Pressing RIGHT"	<< std::endl; }
	if (keystate[SDL_SCANCODE_LEFT])   { std::cout << "Pressing LEFT"	<< std::endl; }
	if (keystate[SDL_SCANCODE_RSHIFT]) { std::cout << "Pressing RSHIFT" << std::endl; }
	if (keystate[SDL_SCANCODE_RCTRL])  { std::cout << "Pressing RCTRL"	<< std::endl; }
	if (keystate[SDL_SCANCODE_W])      { std::cout << "Pressing W"		<< std::endl; }
	if (keystate[SDL_SCANCODE_S])      { std::cout << "Pressing S"		<< std::endl; }
	if (keystate[SDL_SCANCODE_D])      { std::cout << "Pressing D"		<< std::endl; }
	if (keystate[SDL_SCANCODE_A])      { std::cout << "Pressing A"		<< std::endl; }
	if (keystate[SDL_SCANCODE_E])      { std::cout << "Pressing E"		<< std::endl; }
	if (keystate[SDL_SCANCODE_Q])      { std::cout << "Pressing Q"		<< std::endl; }
}

void Draw(Window& window, const vector<Triangle>& triangles)
{
	window.fill(BLACK);

	for (const auto& triangle : triangles)
	{
		vector<vec3> vertices(3);

		vertices[0] = triangle.v0;
		vertices[1] = triangle.v1;
		vertices[2] = triangle.v2;

		// Add drawing
	}
}