#include "List.h"



SDL_WIDGET::List::List() : SDL_WIDGET::Widget()
{
	color.r = 0;
	color.g = 255;
	color.b = 0;
	color.a = 255;

	previous_w = 0;
	previous_h = 0;

	slide_block_width = 10;
	slide_block_rect.w = 10;

	list_texture_ = nullptr;
	unit_height = 20;
	space = 2;
	min_y = 0;
	max_y = 0;
	max_y_constant = 0;
	labels = new std::vector<Label *>();

	handlerMouseMove_ = true;
	slide_block_isPressed = false;
}


SDL_WIDGET::List::~List()
{
	if (labels)
	{
		for (auto it = labels->begin(); it != labels->end(); it++)
		{
			delete (*it);
		}
		delete labels;
	}
	if (list_texture_)
	{
		SDL_DestroyTexture(list_texture_);
	}
}

int SDL_WIDGET::List::getUnitHeight() const
{
	return unit_height;
}

void SDL_WIDGET::List::setUnitHeight(int uh)
{
	if(uh > 0)
		unit_height = uh;
}

char SDL_WIDGET::List::getSpace() const
{
	return space;
}

void SDL_WIDGET::List::setSpace(char s)
{
	if (s >= 0)
		space = s;
}

void SDL_WIDGET::List::setColor(SDL_Color &col)
{
	color = col;
}

const SDL_Color *SDL_WIDGET::List::getColor() const
{
	return &color;
}

void SDL_WIDGET::List::setSlideBlockWidth(int sbw)
{
	slide_block_width = sbw;
	slide_block_rect.w = sbw;
}

int SDL_WIDGET::List::getSlideBlockWidth() const
{
	return slide_block_width;
}

void SDL_WIDGET::List::add(const wchar_t *str,int w)
{
	if (w < 1 || w > rect_.w - slide_block_width)
	{
		w = rect_.w - slide_block_width;
	}
	Label *label = new Label();
	label->renderer_ = this->renderer_;
	label->setSize(w, unit_height);
	label->setPos(0, max_y);
	label->setColor(color);
	label->setText(str);
	labels->push_back(label);

	max_y += unit_height;
	max_y += space;
	max_y_constant += unit_height;
	max_y_constant += space;
	//std::cout << max_y << "\n";
}

void SDL_WIDGET::List::remove(const std::wstring &str)
{
	auto it = labels->begin();
	for (; it != labels->end(); it++)
	{
		if ((*it)->getText() == str)
		{
			delete (*it);
			it = labels->erase(it);
			max_y_constant = max_y_constant - space - unit_height;
			max_y = max_y - space - unit_height;
			break;
		}
	}
	for (; it != labels->end(); it++)
	{
		(*it)->setPos(0, (*it)->rect_.y - space - unit_height);
	}

	removeRepair();
}

void SDL_WIDGET::List::remove(int index)
{
	auto it = labels->begin();
	for (int i = 0; it != labels->end(); it++, i++)
	{
		if (i == index)
		{
			delete (*it);
			it = labels->erase(it);
			max_y_constant = max_y_constant - space - unit_height;
			max_y = max_y - space - unit_height;
			break;
		}
	}
	for (; it != labels->end(); it++)
	{
		(*it)->setPos(0, (*it)->rect_.y - space - unit_height);
	}

	removeRepair();
	
}

void SDL_WIDGET::List::removeRepair()
{
	if (slide_block_isVisible && max_y < rect_.h)
	{
		int t = 0 - min_y;
		t = t > space + unit_height ? space + unit_height : t;
		min_y += t;
		max_y += t;
		for (auto it = labels->begin(); it != labels->end(); it++)
		{
			(*it)->setPos(0, (*it)->rect_.y + t);
		}
	}
}


void SDL_WIDGET::List::rect_update()
{
	if (previous_w != rect_.w || previous_h != rect_.h)
	{
		if (!SDL_RectEmpty(&rect_))
		{
			if (list_texture_)
			{
				SDL_DestroyTexture(list_texture_);
			}
			list_texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect_.w, rect_.h);
			slide_block_rect.x = rect_.w - slide_block_width;
			previous_w = rect_.w;
			previous_h = rect_.h;
		}
	}
}

void SDL_WIDGET::List::draw()
{
	SDL_SetRenderTarget(renderer_, list_texture_);
	SDL_RenderClear(renderer_);

	for (auto it = labels->begin(); it != labels->end(); it++)
	{
		if ((*it)->rect_.y > -unit_height && (*it)->rect_.y < rect_.h)
		{
			(*it)->draw();
		}
	}
	drawSlideBlock();
	SDL_SetRenderTarget(renderer_, NULL);
	SDL_RenderCopy(renderer_, list_texture_, NULL, &rect_);
}

void SDL_WIDGET::List::drawSlideBlock()
{
	if (max_y_constant > rect_.h + space)
	{
		slide_block_isVisible = true;
		float a = (0.0f - (float)min_y) / ((float)(max_y_constant - space));
		slide_block_rect.y = a * rect_.h;
		a = (float)rect_.h / ((float)(max_y_constant - space));
		
		slide_block_rect.h = a * rect_.h;
		SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer_, &slide_block_rect);
	}
	else {
		slide_block_isVisible = false;
	}
}

void SDL_WIDGET::List::mouseButtonDown(int x, int y, int key)
{
	SDL_WIDGET::Widget::mouseButtonDown(x, y, key);
	int i = 0;
	for (; i < labels->size();i++)
	{
		if (labels->at(i)->PointIn(x - rect_.x, y - rect_.y))
		{
			labels->at(i)->mouseButtonDown(x, y, key);
			if (ItemClickCallBack)
			{
				ItemClickCallBack(labels->at(i)->getText(),i);
			}
		}
	}
	SDL_Point p = { x - rect_.x , y - rect_.y };
	if (slide_block_isVisible && SDL_PointInRect(&p, &slide_block_rect))
	{
		slide_block_isPressed = true;
		slide_block_pressed_y = y;
	}
}
void SDL_WIDGET::List::mouseButtonUp(int x, int y, int key)
{
	for (auto it = labels->begin(); it != labels->end(); it++)
	{
		if ((*it)->PointIn(x - rect_.x, y - rect_.y))
		{
			(*it)->mouseButtonUp(x, y, key);
		}
	}
	
	if (slide_block_isPressed)
	{
		slide_block_isPressed = false;
	}
}

void SDL_WIDGET::List::mouseMove(int x, int y)
{
	for (auto it = labels->begin(); it != labels->end(); it++)
	{
		(*it)->onMouseOver_ = false;
		if ((*it)->PointIn(x - rect_.x, y - rect_.y))
		{
			(*it)->onMouseOver_ = true;
			(*it)->mouseMove(x, y);
		}
	}
	if (slide_block_isPressed)
	{
		int offset = (y - slide_block_pressed_y) * (max_y_constant / rect_.h);
		if (min_y  <= 0 && min_y >= -(max_y_constant - rect_.h))
		{
			if (min_y - offset > 0 || min_y - offset <= -(max_y_constant - rect_.h))
			{
				slide_block_pressed_y = y;
				return;
			}
			min_y -= offset;
			max_y -= offset;
			std::cout << min_y << "  " << max_y << std::endl;
			for (auto it = labels->begin(); it != labels->end(); it++)
			{
				(*it)->setPos(0, (*it)->rect_.y - offset);
			}
		}
		slide_block_pressed_y = y;
	}
}

void SDL_WIDGET::List::mouseWheel( int direction)
{
	int offset = -direction * 10;
	if (min_y <= 0 && min_y >= -(max_y_constant - rect_.h))
	{
		if (min_y - offset > 0 || min_y - offset <= -(max_y_constant - rect_.h))
		{
			slide_block_pressed_y -= offset;
			return;
		}
		min_y -= offset;
		max_y -= offset;
		std::cout << min_y << "  " << max_y << std::endl;
		for (auto it = labels->begin(); it != labels->end(); it++)
		{
			(*it)->setPos(0, (*it)->rect_.y - offset);
		}
	}
	slide_block_pressed_y -= offset;
}

void SDL_WIDGET::List::setItemClickCallBack(ItemClickCallBackType itemClickCallBack)
{
	ItemClickCallBack = itemClickCallBack;
}



