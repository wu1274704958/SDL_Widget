#include "Widget.h"

SDL_WIDGET::Widget::Widget()
{
	onMouseOver_ = false;
	visible_ = true;
	handlerMouseMove_ = false;
	onFocus_ = false;
}

SDL_WIDGET::Widget::Widget(const Widget &w)
{
	onMouseOver_ = w.onMouseOver_;
	clickCallBack_ = w.clickCallBack_;
	visible_ = w.visible_;
	handlerMouseMove_ = w.handlerMouseMove_;
	onFocus_ = w.onFocus_;
	rect_ = w.rect_;
}

SDL_WIDGET::Widget::~Widget()
{

}

void SDL_WIDGET::Widget::setOnClickCallBack(std::function<void(Widget*)>&& f)
{
	clickCallBack_ = f;
}

void SDL_WIDGET::Widget::mouseButtonDown(int x, int y, int key)
{
	if (clickCallBack_)
	{
		clickCallBack_(this);
	}
}

bool &SDL_WIDGET::Widget::isHandlerMouseMove()
{
	return handlerMouseMove_;
}

bool &SDL_WIDGET::Widget::isVisible()
{
	return visible_;
}

void SDL_WIDGET::Widget::setPos(int x, int y)
{
	rect_.x = x;
	rect_.y = y;
	rect_update();
}

void SDL_WIDGET::Widget::setSize(int w, int h)
{
	rect_.w = w;
	rect_.h = h;
	rect_update();
}

void SDL_WIDGET::Widget::setRect(SDL_Rect& r)
{
	rect_ = r;
	rect_update();
}

bool SDL_WIDGET::Widget::PointIn(int x, int y)
{
	SDL_Point p = { x,y };
	return SDL_PointInRect(&p, &rect_);
}