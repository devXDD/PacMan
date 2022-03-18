#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "AssetManager.h"
#include <string>
#include <iostream>

Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer) : myWindow(aWindow), myRenderer(aRenderer)
{
}

Drawer::~Drawer(void)
{
}

bool Drawer::Init()
{
	if (!myWindow)
		return false;

	return true;
}

void Drawer::Draw(std::string anImage, int aCellX, int aCellY)
{
	SDL_Surface* surfacee = AssetManager::Get().GetSurface(anImage);
//	SDL_Surface* surfacee = IMG_Load(anImage);
	if (!surfacee)
	{ 
		std::cout << "Surface not created: " << std::endl;
		return;
	}
	
	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surfacee);
	//SDL_FreeSurface(surfacee);
	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surfacee->w;
	sizeRect.h = surfacee->h;
	SDL_Rect posRect;
	posRect.x = aCellX;
	posRect.y = aCellY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;
	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);

}
void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY)
{
	TTF_Font* font = TTF_OpenFont(aFontFile, 24);

	SDL_Color fg = { 255,0,0,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = aX;
	posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}