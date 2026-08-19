#pragma once
#include"plant_registry.h"
struct plant_card {
	plant_card(Planttype t) : type(t) {}
	Planttype type;
	int x, y;
	bool isSelected = false;
};

class plant_pool {
public:
	void add_plant(plant_card card) {
		plantpool.push_back(card);
	}
	void update();
private:
	std::vector<plant_card> plantpool;
};