// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "SDL_helper.h"


using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;


// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw(Window& window);


// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{
    Window window = Window::Create("Lab1", SCREEN_WIDTH, SCREEN_HEIGHT);

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

        Draw(window);

        // NOTE: The pixels are not shown on the screen 
        // until we update the window with this method.
        window.update();
    }

    window.screenshot();

    Window::Destroy(&window);
    return 0;
}

void Draw(Window& window)
{
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            vec3 color(0, 0, 1);
            window.set_pixel(x, y, color);
        }
    }

    // The same can be acheived with:
    // window.fill(BLUE);
}