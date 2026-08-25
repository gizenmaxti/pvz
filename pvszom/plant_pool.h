#pragma once
#include"plant_registry.h"

class plant_pool {
public:
	void add_plant(Planttype t) {
		plantpool.push_back(t);
	}
	const std::vector<Planttype>&getplanttype()const {
		return plantpool;
	}
	void update();
private:
	std::vector<Planttype> plantpool;
};