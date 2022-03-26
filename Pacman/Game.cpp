#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"
#include "pacman.h"
#include "drawer.h"
#include <iostream>

Game::Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		std::cout << "Initiazlized! " << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window)
		{
			std::cout << "Window created: " << std::endl;
		}
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		if (TTF_Init() == -1)
		{
			assert(0 && "Failed to create ttf!");
			exit(-1);
		}




		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvents()
{
	Drawer* drawer = Drawer::Create(window, renderer);
	Pacman* pacman = Pacman::Create(drawer);
	float lastFrame = (float)SDL_GetTicks() * 0.001f;
	float currentFrame = (float)SDL_GetTicks() * 0.001f;
	float elapsedTime = currentFrame - lastFrame;
	SDL_Event event;
	SDL_PollEvent(&event);

	if (!pacman->Update(elapsedTime))
		isRunning = false;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	pacman->Draw();
	//pacman->myNextMovement = Vector2f(0.f, -1.f);	
	lastFrame = currentFrame;


	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	if (event.type == SDL_QUIT)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}
void Game::update()
{

}
void Game::render()
{
}

void Game::clean()
{


	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
