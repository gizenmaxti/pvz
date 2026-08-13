#pragma once
#include <easyx.h>
#include "scene.h"
class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
private:
	IMAGE background,shop;
};