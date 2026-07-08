#pragma once
#include "game.h"
#include "scene.h"
struct level {
	int levelnum;
	int sun;
	int zombiecount;
	int time;
	int id;
};
class adventure_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
private:
	IMAGE background;
	level levels[2];
};