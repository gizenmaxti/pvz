#pragma once
#include <easyx.h>
#include<memory>
#include "scene.h"
#include "level_registry.h"
#include "plant_pool.h"
#include"Button.h"
#include"grassland.h"
enum process {
	ready,
	fight,
	win,
	fail
};


struct product {
	product(Planttype rt):t(rt) {
		cooldown = plant_registry::instance().get_plant_info(t).cooldown;
	}
	Planttype t;
	int cooldown;
};

class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void ready();
	void fight();
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	grassland g;
	std::optional<Planttype>selectplant = std:: nullopt;
	process curprocess=process::ready;
	levelinfo levelconfig;
	plant_pool pool;
	//std::vector<Planttype>shop;
	std::vector<product>shop;
	level curlevel;
	IMAGE background,shopimg,poolimg;
	std::unique_ptr<Basicbutton>start;
};