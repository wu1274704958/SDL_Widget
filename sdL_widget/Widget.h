#pragma once
#ifndef __SDL_WIDGET_WIDGET_H_
#define __SDL_WIDGET_WIDGET_H_


namespace SDL_WIDGET
{
	class Widget;
}

#include <SDL.h>
#include <iostream>
#include <functional>

class SDL_WIDGET::Widget
{
	friend class Window;
private:
	std::function<void(Widget*)> clickCallBack_;

protected:
	SDL_Rect rect_;
	bool visible_;
	bool handlerMouseMove_;
	bool onFocus_;
	bool onMouseOver_;
	SDL_Renderer *renderer_;

public:

	Widget();

	Widget(const Widget &w);

	virtual ~Widget();

	void setOnClickCallBack(std::function<void(Widget*)>&& f);

	virtual void keyDown(Uint32 key){}
	virtual void keyUp(Uint32 key){}
	virtual void mouseButtonDown(int x, int y, int key);
	virtual void mouseButtonUp(int x,int y,int key){}
	virtual void mouseMove(int x,int y){}
	virtual void mouseWheel(int direction){}

	virtual void draw(){}

	virtual void rect_update() {}

	bool &isHandlerMouseMove();
	bool &isVisible();
	void setPos(int x, int y);
	void setSize(int w, int h);
	void setRect(SDL_Rect& r);
	
	bool PointIn(int x, int y);
};

#endif //__SDL_WIDGET_WIDGET_H_