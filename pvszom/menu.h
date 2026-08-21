#pragma once
#include <easyx.h>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "scene.h"
#include "Button.h"
#include "tool.h"

class menubutton :public Button{
public:
	menubutton(int x, int y, int w, int h, const std::string &imgpath, const std::string& hoverpath, std::function<std::unique_ptr<scene>()>factory) :
		Button(x, y, w, h,imgpath,hoverpath), target(std::move(factory)){

	}
	void onClick(bool clicked);

	bool ishover(int mousex, int mousey) const {
		return mousex >= getx() && mousex < getx() + getw() && mousey >= gety()+40 && mousey < gety()-20 + geth();
	}

	void hover(bool hovered) override;
	
private:
	std::function<std::unique_ptr<scene>()>target = nullptr;
};


class MenuScene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
private:
	IMAGE menu_begin;
	
	std::vector<menubutton>buttons;
	void draw_button();
};