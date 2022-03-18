#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"

class Game
{

	private:

		SDL_Window* window;
		SDL_Renderer* renderer;
		bool isRunning;
		
	

	public:
		Game();
	
		
		void init(const char* title, int xpos, int ypos, int width, int height);

		void handleEvents();
		void update();
		void render();
		void clean();
		bool running()
		{
			return isRunning;
		}

};
#endif // !Game_h
