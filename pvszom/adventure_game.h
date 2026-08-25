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

	void getlevel(level l) {
		curlevel = l;
	}

private:
	const levelinfo& levelconfig = level_registry::instance().get_levelinfo(curlevel);
	const plant_pool& pool = levelconfig.pool;
	std::vector<Planttype>product;
	level curlevel;
	IMAGE background,shop,poolimg;
};