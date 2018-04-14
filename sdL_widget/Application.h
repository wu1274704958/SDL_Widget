#pragma once
#ifndef __SDL_WIDGET_APPLICATION_H_
#define __SDL_WIDGET_APPLICATION_H_

namespace SDL_WIDGET
{
	class Application;
}

#include <SDL.h>
#include <SDL_ttf.h>
#include "FontManager.h"

class SDL_WIDGET::Application
{
public:
	
	Application();
	Application(const Application &) = delete;
	Application(Application &&) = delete;
	~Application();
};


#endif //__SDL_WIDGET_APPLICATION_H_