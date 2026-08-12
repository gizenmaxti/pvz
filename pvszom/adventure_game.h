#pragma once
#include <easyx.h>
#include "scene.h"
class adventure_game_Scene : public scene {
public:
	void load() override {
		loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
		loadimage(&shop, "res\\images\\adventure_game\\wd.jpg", 650, 100);
	}
	void update() override;
	void unload() override {
	}
private:
	IMAGE background,shop;

};