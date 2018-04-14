#include "Window.h"
#include "Label.h"
#include "List.h"

SDL_WIDGET::Window::Window(const char *title, int x, int y, int w, int h, bool handware)
{

	clearColor.r = 0;
	clearColor.g = 0;
	clearColor.b = 0;
	clearColor.a = 255;

	handlerMouseMove_ = true;
	isStillRunning_ = true;
	lastFrameTime_ = 19;
	sleep_t_ = 18;

	w_ = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);

	if (renderer_ == NULL)
	{
		if (handware)
		{
			renderer_ = SDL_CreateRenderer(w_, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
		}
		else {
			renderer_ = SDL_CreateRenderer(w_, -1, SDL_RendererFlags::SDL_RENDERER_SOFTWARE);
		}
	}

	event_ = new SDL_Event();
	ws_ = new std::set<Widget *>();
}

SDL_WIDGET::Window::~Window()
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		delete (*it);
	}
	delete ws_;
	delete event_;
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(w_);
}


void SDL_WIDGET::Window::destroyWidget(Widget * widget)
{
	will_erase.push_back(widget);
}

SDL_Color &SDL_WIDGET::Window::getClearColor()
{
	return clearColor;
}

void SDL_WIDGET::Window::draw()
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		if ((*it)->isVisible())
		{
			(*it)->draw();
		}
	}
	for (int i = 0; i < will_erase.size(); i++)
	{
		for (auto it = ws_->begin(); it != ws_->end(); it++)
		{
			if (will_erase.at(i) == (*it))
			{
				delete (*it);
				ws_->erase(it);
				break;
			}
		}
	}
	if (!will_erase.empty())
	{
		will_erase.clear();
	}
}

void SDL_WIDGET::Window::keyDown(Uint32 key)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		if ((*it)->isVisible() && (*it)->onFocus_)
		{
			(*it)->keyDown(key);
		}
	}
}

void SDL_WIDGET::Window::keyUp(Uint32 key)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		if ((*it)->isVisible() && (*it)->onFocus_)
		{
			(*it)->keyUp(key);
		}
	}
}

void SDL_WIDGET::Window::mouseButtonDown(int x, int y, int key)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		(*it)->onFocus_ = false;
		if ((*it)->isVisible() && (*it)->PointIn(x, y))
		{
			(*it)->onFocus_ = true;
			(*it)->mouseButtonDown(x, y, key);
		}
	}
}

void SDL_WIDGET::Window::mouseButtonUp(int x, int y, int key)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		if ((*it)->isVisible() && (*it)->PointIn(x, y))
		{
			(*it)->mouseButtonUp(x, y, key);
		}
	}
}

void SDL_WIDGET::Window::mouseMove(int x, int y)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		(*it)->onMouseOver_ = false;
		if ((*it)->isVisible() && (*it)->PointIn(x, y) && (*it)->handlerMouseMove_)
		{
			(*it)->onMouseOver_ = true;
			(*it)->mouseMove(x, y);
		}
	}
}

void SDL_WIDGET::Window::mouseWheel(int direction)
{
	for (auto it = ws_->begin(); it != ws_->end(); it++)
	{
		if ((*it)->isVisible() && (*it)->onMouseOver_)
		{
			(*it)->mouseWheel(direction);
		}
	}
}

bool& SDL_WIDGET::Window::isHandlerMouseMove()
{
	return handlerMouseMove_;
}

void SDL_WIDGET::Window::mainLoop()
{
	while (isStillRunning_)
	{
		long start = ::SDL_GetTicks();

		SDL_SetRenderDrawColor(renderer_, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		SDL_RenderClear(renderer_);

		if (::SDL_PollEvent(event_))
		{
			switch (event_->type)
			{
			case SDL_QUIT:
				isStillRunning_ = false;
				break;
			case SDL_KEYDOWN:
				keyDown(event_->key.keysym.sym);
				break;
			case SDL_KEYUP:
				keyUp(event_->key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event_->button.clicks == 1)
					mouseButtonDown(event_->button.x, event_->button.y, event_->button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				if (event_->button.clicks == 1)
					mouseButtonUp(event_->button.x, event_->button.y, event_->button.button);
				break;
			case SDL_MOUSEMOTION:
				if (handlerMouseMove_)
					mouseMove(event_->motion.x, event_->motion.y);
				break;
			case SDL_MOUSEWHEEL:
				mouseWheel(event_->wheel.y);
			default:
				break;
			}
		}


		draw();
		::SDL_RenderPresent(renderer_);



		if (lastFrameTime_ > 18)
		{
			sleep_t_ = (sleep_t_ >= 2 ? sleep_t_ - 1 : sleep_t_);
		}
		if (lastFrameTime_ < 16)
		{
			sleep_t_++;
		}

		//std::cout << 1000 / lastFrameTime_ << std::endl;
		SDL_Delay(sleep_t_);

		long end = ::SDL_GetTicks();
		lastFrameTime_ = end - start;

	}
}
