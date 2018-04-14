#include "Label.h"


SDL_WIDGET::Label::Label() : Widget()
{
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	rect_.x = rect_.y = 0;
	rect_.w = rect_.h = 10;

	update_rect_pressed();

	texture_ = nullptr;
	isPressed = false;

	handlerMouseMove_ = true;
}

SDL_WIDGET::Label::Label(const Label& label) : Widget(label)
{
	if (!label.text_.empty())
	{
		text_ = label.text_;
		color = label.color;
		isPressed = label.isPressed;
		rect_pressed = label.rect_pressed;

		TTF_Font * font = FontManager::GetInstance()->getDefault();
		SDL_Color c = { 255,255,255,255 };
		SDL_Surface * temp = ::TTF_RenderUNICODE_Blended(font, reinterpret_cast<const Uint16 *>(text_.c_str()), c);
		texture_ = SDL_CreateTextureFromSurface(renderer_, temp);
		::SDL_FreeSurface(temp);
	}
}

SDL_WIDGET::Label::~Label()
{
	if (texture_)
		::SDL_DestroyTexture(texture_);
	std::cout << " ~Label()" << std::endl;
}

void SDL_WIDGET::Label::update_rect_pressed()
{
	rect_pressed.x = rect_.x + 3;
	rect_pressed.y = rect_.y + 3;
	rect_pressed.w = rect_.w - 6;
	rect_pressed.h = rect_.h - 6;
}

void SDL_WIDGET::Label::rect_update()
{
	update_rect_pressed();
}

const std::wstring &SDL_WIDGET::Label::getText()
{
	return text_;
}

void SDL_WIDGET::Label::mouseButtonDown(int x, int y, int key)
{
	Widget::mouseButtonDown(x, y, key);
	isPressed = true;
}

void SDL_WIDGET::Label::mouseButtonUp(int x, int y, int key)
{
	isPressed = false;
}

void SDL_WIDGET::Label::setText(const wchar_t *str)
{
	//cout << str << endl;
	bool flag = false;
	if (text_.empty())
	{
		text_ = str;
		flag = true;
	}
	if (flag == false && text_ != str) // text_ not equse str
	{
		text_ = str;
		flag = true;
	}
	if (flag)
	{
		if (texture_)
			::SDL_DestroyTexture(texture_);


		TTF_Font * font = FontManager::GetInstance()->getDefault();
		SDL_Color c = { 255,255,255,255 };
		SDL_Surface * temp = ::TTF_RenderUNICODE_Blended(font, reinterpret_cast<const Uint16 *>(str), c);
		texture_ = SDL_CreateTextureFromSurface(renderer_, temp);
		::SDL_FreeSurface(temp);
	}
}

void SDL_WIDGET::Label::setColor(SDL_Color &col)
{
	color = col;
}

void SDL_WIDGET::Label::draw()
{
	if (onMouseOver_)
	{
		//SDL_SetTextureColorMod(texture_, 255 - color.r, 255 - color.g, 255 - color.b);
		SDL_Color quondam;
		SDL_GetRenderDrawColor(renderer_, &quondam.r, &quondam.g, &quondam.b, &quondam.a);
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
		if (isPressed)
		{
			SDL_RenderDrawRect(renderer_, &rect_pressed);
		}
		else {
			SDL_RenderDrawRect(renderer_, &rect_);
		}
		SDL_SetRenderDrawColor(renderer_, quondam.r, quondam.g, quondam.b, quondam.a);
	}

	SDL_SetTextureColorMod(texture_, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture_, color.a);


	if (isPressed)
	{
		SDL_RenderCopy(renderer_, texture_, NULL, &rect_pressed);
	}
	else {
		SDL_RenderCopy(renderer_, texture_, NULL, &rect_);
	}
}