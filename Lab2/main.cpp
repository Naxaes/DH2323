#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "SDL_helper.h"
#include "TestModel.h"


using glm::vec3;
using glm::mat3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;


// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Update(float dt);
void Draw(Window& window);



// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{
    Window window = Window::Create("Lab2", SCREEN_WIDTH, SCREEN_HEIGHT);
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
        Draw(window);

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

    const Uint8* key_state = SDL_GetKeyboardState(nullptr);

    if (key_state[SDL_SCANCODE_UP])     { std::cout << "Pressing UP"     << std::endl; }
    if (key_state[SDL_SCANCODE_DOWN])   { std::cout << "Pressing DOWN"   << std::endl; }
    if (key_state[SDL_SCANCODE_LEFT])   { std::cout << "Pressing LEFT"   << std::endl; }
    if (key_state[SDL_SCANCODE_RIGHT])  { std::cout << "Pressing RIGHT"  << std::endl; }
    if (key_state[SDL_SCANCODE_RSHIFT]) { std::cout << "Pressing RSHIFT" << std::endl; }
    if (key_state[SDL_SCANCODE_RCTRL])  { std::cout << "Pressing RCTRL"  << std::endl; }
    if (key_state[SDL_SCANCODE_W])      { std::cout << "Pressing W"      << std::endl; }
    if (key_state[SDL_SCANCODE_S])      { std::cout << "Pressing S"      << std::endl; }
    if (key_state[SDL_SCANCODE_A])      { std::cout << "Pressing A"      << std::endl; }
    if (key_state[SDL_SCANCODE_D])      { std::cout << "Pressing D"      << std::endl; }
    if (key_state[SDL_SCANCODE_E])      { std::cout << "Pressing E"      << std::endl; }
    if (key_state[SDL_SCANCODE_Q])      { std::cout << "Pressing Q"      << std::endl; }
}

void Draw(Window& window)
{
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            vec3 color(1, 0.5, 0.5);
            window.set_pixel(x, y, color);
        }
    }
}
