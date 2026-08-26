#pragma once
#include <easyx.h>
#include "scene.h"
#include "level_registry.h"
#include "plant_pool.h"


struct product {
	Planttype t;
	int cooldown = plant_registry::instance().get_plant_info(t).cooldown;
};

class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void ready();
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	levelinfo levelconfig;
	plant_pool pool;
	std::vector<Planttype>shop;
	level curlevel;
	IMAGE background,shopimg,poolimg;
};