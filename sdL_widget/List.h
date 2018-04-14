#pragma once
#ifndef __SDL_WIDGET_LIST_H_
#define __SDL_WIDGET_LIST_H_


namespace SDL_WIDGET {
	class List;
}
#include "Widget.h"
#include <SDL.h>
#include <vector>
#include "Label.h"

class SDL_WIDGET::List : public Widget
{
	typedef std::function<void(const std::wstring &str, int index)> ItemClickCallBackType;
private:
	SDL_Texture * list_texture_;
	int unit_height;
	char space;
	std::vector<Label *> *labels;
	SDL_Color color;
	SDL_Rect slide_block_rect;
	int max_y;
	int max_y_constant;
	int min_y;
	int slide_block_width;
	int previous_w;
	int previous_h;
	bool slide_block_isPressed;
	bool slide_block_isVisible;
	int slide_block_pressed_y;
	ItemClickCallBackType ItemClickCallBack;
public:
	List();
	virtual ~List();
	void setSpace(char s);
	char getSpace() const;
	void setUnitHeight(int uh);
	int getUnitHeight() const;
	void add(const wchar_t *,int);
	void setColor(SDL_Color &);
	const SDL_Color* getColor() const;
	void setSlideBlockWidth(int sbw);
	int getSlideBlockWidth() const;
	virtual void rect_update();
	virtual void draw();
	virtual void mouseButtonDown(int x, int y, int key);
	virtual void mouseButtonUp(int x, int y, int key);
	virtual void mouseMove(int x, int y);
	virtual void mouseWheel( int direction);
	void setItemClickCallBack(ItemClickCallBackType itemClickCallBack);
	void remove(const std::wstring &str);
	void remove(int index);
private:
	void removeRepair();
	void drawSlideBlock();
};


#endif //__SDL_WIDGET_LIST_H_

