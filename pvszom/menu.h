#pragma once
#include "game.h"
#include "scene.h"
//extern void loadgame_begin_image();
//extern void update_gamebegin();

struct button {
	int x, y, width, height;
	IMAGE img, select_img;
};

class MenuScene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
private:
	IMAGE menu_begin;
	static const int button_count = 4;
	button buttons[button_count];
	bool select_button(int x, int y, button b);
	void draw_button();
};