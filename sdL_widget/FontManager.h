#pragma once
#ifndef __SDL_WIDGET_FONT_MANAGER_H_
#define __SDL_WIDGET_FONT_MANAGER_H_

#include <iostream>
#include <map>
#include <SDL_ttf.h>
#include <string>

namespace SDL_WIDGET
{
	class FontManager;
}

class SDL_WIDGET::FontManager
{
public:
	static FontManager self;
	static const char *defaultFontPath;
private:
	FontManager()
	{

	}
	FontManager(const FontManager &) = delete;
	FontManager(FontManager &&) = delete;

	std::map<std::string, TTF_Font *> data;

public:
	static FontManager *GetInstance()
	{
		return &self;
	}

	void load(const char *name,int fsize)
	{
		if (fsize < 1 || fsize > 255)
		{
			throw "fsize do not conform to the rules!";
		}
		std::string path("resources/fonts/");
		path += name;
		TTF_Font *font = TTF_OpenFont(path.c_str(),fsize);
		if (font == NULL)
		{
			throw "Open Font Failed!";
		}
		std::string str(name);
		
		char num[4] = { 0 };
		_itoa_s(fsize, num, 10);
		str += num;
		data.insert(std::make_pair(str, font));

	}
	TTF_Font *get(const char *name)
	{
		auto a = data.find(std::string(name));
		if (a == data.end())
		{
			return nullptr;
		}
		return a->second;
	}

	TTF_Font *getDefault()
	{
		return get("simkai.ttf40");
	}

	void loadDefault()
	{
		load(defaultFontPath, 40);
	}

	void closeAllFont()
	{
		for (auto a : data)
		{
			if (a.second)
			{
				TTF_CloseFont(a.second);
			}
		}
	}
};



#endif //__SDL_WIDGET_FONT_MANAGER_H_