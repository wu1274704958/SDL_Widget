#include "Application.h"

SDL_WIDGET::Application::Application()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw "SDL2 Init Failed!";
	}
	if (TTF_Init())
	{
		throw "SDL_ttf Init Failed!";
	}
	FontManager::GetInstance()->loadDefault();
}

SDL_WIDGET::Application::~Application()
{
	FontManager::GetInstance()->closeAllFont();

	TTF_Quit();
	SDL_Quit();
}