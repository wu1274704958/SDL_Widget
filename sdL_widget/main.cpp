
 
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Window.h"
#include "Label.h"
#include "Application.h"
#include "FontManager.h"
#include "List.h"
#include <wchar.h>

int main(int argc,char *argv[])
{
	
	SDL_WIDGET::Application app;

	SDL_WIDGET::Window w("SDL_t2",20,20,500,600);

	SDL_WIDGET::Label *label = w.createWidget<SDL_WIDGET::Label>();
	label->setPos(0, 0);
	label->setSize(80,35);

	label->setText(L"删除我");
	label->setOnClickCallBack([&w](auto widget)->void {
		w.destroyWidget(widget);
	});

	SDL_WIDGET::Label *label2 = w.createWidget<SDL_WIDGET::Label>();
	label2->setPos(40, 0);
	label2->setSize(85, 35);

	label2->setText(L"删除我2");
	label2->setOnClickCallBack([&w](auto widget)->void {
		w.destroyWidget(widget);
	});

	SDL_WIDGET::List *list = w.createWidget<SDL_WIDGET::List>();
	SDL_Rect rect = { 80,80,300,300 };
	SDL_Color color = { 0,0,255,180 };
	list->setColor(color);
	list->setUnitHeight(40);
	list->setSpace(3);
	list->setSlideBlockWidth(30);
	list->setRect(rect);
	list->add(L"AAAAAAAAA",-1);
	list->add(L"你好", 80);
	/*list->add(L"BBBBBBBBB");
	list->add(L"CCCCCCCCC");
	list->add(L"DDDDDDDDD");
	list->add(L"EEEEEEEEE");
	list->add(L"FFFFFFFFF");
	list->add(L"GGGGGGGGG");
	list->add(L"HHHHHHHHH");
	list->add(L"IIIIIIIII");
	list->add(L"JJJJJJJJJ");
	list->add(L"KKKKKKKKK");*/
	list->setItemClickCallBack([list](const std::wstring &str,int index)->void {
		std::cout << index << std::endl;
		switch (index)
		{
		case 0:
			list->add(L"AWEewsWES",200);
			break;
		default:
			//list->remove(str);
			break;
		}
	});

	w.mainLoop();
	return 0;
}


void test_one()
{
	/*SDL_WIDGET::Label *l = w.createWidget<SDL_WIDGET::Label>();
	SDL_Color col = { 0,255,0,255 };
	SDL_Rect r = { 0,0,120,40 };
	l->setColor(col);
	l->setRect(r);
	l->setText(L"aaaa");
	l->setOnClickCallBack([](SDL_WIDGET::Widget *w)->void {std::cout << "aaaa" << std::endl; });

	SDL_WIDGET::Label *l2 = w.createWidget<SDL_WIDGET::Label>();
	r.x = 0;
	r.y = 20;
	col.g -= 50;
	l2->setColor(col);
	l2->setRect(r);
	l2->setText(L"开始");
	l2->setOnClickCallBack([&col, &w](SDL_WIDGET::Widget *widget)->void {
		col.r = 255;
		col.g = 0;
		dynamic_cast<SDL_WIDGET::Label *>(widget)->setColor(col);
		w.getClearColor().b = 150;
	});

	SDL_WIDGET::Label *l3 = w.createWidget<SDL_WIDGET::Label>();
	r.x = 0;
	r.y = 80;
	col.g -= 50;
	col.b += 78;
	l3->setColor(col);
	l3->setRect(r);
	l3->setText(L"cccc");
	l3->setOnClickCallBack([](SDL_WIDGET::Widget *w)->void {std::cout << "cccc" << std::endl; });*/
}

