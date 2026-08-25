#pragma once
#include <easyx.h>
#include "scene.h"
#include "level_registry.h"
class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	levelinfo levelconfig;
	plant_pool pool;
	std::vector<Planttype>product;
	level curlevel;
	IMAGE background,shop,poolimg;
};