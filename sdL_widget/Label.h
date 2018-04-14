#pragma once
#ifndef __SDL_WIDGET_LABEL_H_
#define __SDL_WIDGET_LABEL_H_



namespace SDL_WIDGET
{
	class Label;
}

#include <SDL.h>
#include <iostream>
#include "Widget.h"
#include "FontManager.h"

class SDL_WIDGET::Label : public Widget
{
	friend class List;
private:
	SDL_Rect rect_pressed;
	SDL_Texture *texture_;
	SDL_Color color;
	std::wstring text_;
	bool isPressed;
public:
	Label();

	Label(const Label& label);

	Label(Label &&) = delete;

	void update_rect_pressed();

	virtual void rect_update();


	const std::wstring &getText();

	virtual void mouseButtonDown(int x, int y, int key);

	virtual void mouseButtonUp(int x, int y, int key);

	void setText(const wchar_t *str);
	
	void setColor(SDL_Color &col);

	virtual ~Label();

	virtual void draw();
};


#endif //__SDL_WIDGET_LABEL_H_