#pragma once
#include <easyx.h>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "scene.h"
#include "Button.h"
#include "tool.h"
#include"level.h"

//#define COUNT_LEVEL 15

class adventure_button :public Button {
//public:
//	adventure_button(int x, int y, int w, int h, const std::string& imgpath, const std::string& hoverpath, std::function<std::unique_ptr<scene>()>factory) :
//		Button(x, y, w, h, imgpath, hoverpath), target(std::move(factory)) {
//	}
//	void onClick(bool clicked) override {
//		if (clicked) {
//			clicked = false;
//			sceneManager.changeScene(Action::push, target());
//		}
//	}
//	bool ishover(int mousex, int mousey) const {
//		return mousex >= getx() && mousex < getx() + getw() && mousey >= gety() && mousey < gety() + geth();
//	}
//	void hover(bool hovered) override {
//		if (hovered) {
//			putimagePNG(getx(), gety(), &gethover());
//			onClick(clicked);
//		}
//		else {
//			putimagePNG(getx(), gety(), &getimg());
//		}
//	}
//private:
//	std::function<std::unique_ptr<scene>()>target = nullptr;
};

class adventure_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void addlevel(const level& l) {
		level_list.push_back(l);
	}
	
private:
	void draw_level();
	IMAGE background, background2;
	IMAGE return_button, return_bbutton;
	void returnbutton();
	std::vector<level> level_list;
};
