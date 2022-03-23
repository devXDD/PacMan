#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"
#include "pacman.h"
#include "drawer.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		assert(0 && "Failed to initialize video!");
		exit(-1);
	}

	window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Testing Joytick Support

	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	std::cout << "Controller Name: " << SDL_JoystickName(joystick) << std::endl;
	std::cout << "Controller Axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
	std::cout << "Controller Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;
	*/
	if (!window)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}



	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}

	Drawer* drawer = Drawer::Create(window, renderer);
	Pacman* pacman = Pacman::Create(drawer);



	float lastFrame = (float)SDL_GetTicks() * 0.001f;
	SDL_Event event;
	while (SDL_PollEvent(&event) >= 0)
	{
		float currentFrame = (float)SDL_GetTicks() * 0.001f;
		float elapsedTime = currentFrame - lastFrame;
		if (!pacman->Update(elapsedTime))
			break;
		if (event.type == SDL_QUIT)
		{
			break;
		}

		/* Joystick Event Handling
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
				if (event.jaxis.which == 1)
				{
					if (event.jbutton.button == 0)
					{
						std::cout << "Button pressed!";
						pacman->myNextMovement = Vector2f(0.f, -1.f);
					}
				}
			}
		*/

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		pacman->Draw();
		//pacman->myNextMovement = Vector2f(0.f, -1.f);	
		lastFrame = currentFrame;

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	delete pacman;
	delete drawer;

	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(window);


	SDL_Quit();
	return 0;
}