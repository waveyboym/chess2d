#include "SDL_Handler.h"

int main(int argc, char* args[])
{
	SDL_Handler obj;
	//Start up SDL and create window
	if (!obj.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		{
			//Main loop flag
			bool quit = false;

			if (!obj.initPictures()) 
			{
				printf("failed to initialize pictures!\n");
				obj.close();
				return 0;
			}
			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					obj.handleEvent(&e);
				}

				obj.displayStuff();
			}
		}
	}

	//Free resources and close SDL
	obj.close();

	return 0;
}