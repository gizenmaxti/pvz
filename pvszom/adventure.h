#pragma once
#include <easyx.h>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "scene.h"
#include "Button.h"
#include "tool.h"
#include"level_registry.h"


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
