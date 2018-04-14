#pragma once
#ifndef __SDL_WIDGET_WINDOW_H_
#define __SDL_WIDGET_WINDOW_H_


namespace SDL_WIDGET
{
	class Window;
}

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <set>
#include <vector> 
#include "Widget.h"

class SDL_WIDGET::Window{
private:
	SDL_Window *w_;
	Uint32 lastFrameTime_;
	Uint8 sleep_t_; 
	bool isStillRunning_;
	SDL_Event *event_;
	bool handlerMouseMove_;
	std::set<Widget *> *ws_;
	SDL_Renderer *renderer_;
	SDL_Color clearColor;
	std::vector<Widget *>will_erase;
public:

	Window(const char *title, int x, int y, int w, int h, bool handware = true);

	Window(const Window &) = delete;
	Window(Window &&) = delete;

	virtual ~Window();

	template<typename T>
	T * createWidget()
	{
		T *widget = new T();
		ws_->insert(widget);
		widget->renderer_ = renderer_;
		return widget;
	}

	void destroyWidget(Widget * widget);

	SDL_Color &getClearColor();

	virtual void draw();

	virtual void keyDown(Uint32 key);
	virtual void keyUp(Uint32 key);
	virtual void mouseButtonDown(int x, int y, int key);
	virtual void mouseButtonUp(int x, int y, int key);
	
	virtual void mouseMove(int x, int y);

	virtual void mouseWheel(int direction);
	
	bool& isHandlerMouseMove();

	void mainLoop();
};


#endif //__SDL_WIDGET_WINDOW_H_