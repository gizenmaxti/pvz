#pragma once
#include"plant_registry.h"
struct poolinfo {
	Planttype t;
	bool optional;
};

class plant_pool {
public:
	void add_plant(Planttype t) {
		poolinfo p;
		p.optional = true;
		p.t = t;
		plantpool.push_back(p);
	}
	std::vector<poolinfo>& getplanttype() {
		return plantpool;
	}
	void update();
private:
	//std::vector<Planttype> plantpool;
	std::vector<poolinfo> plantpool;
};