#pragma once
#include<unordered_map>
#include"plantinfo.h"
class plant_registry {
public:
	static plant_registry& instance() {
		static plant_registry instance;
		return instance;
	}
	void load();
	void update();
	const plantinfo& get_plant_info(Planttype type) const {
		return plant_infos.at(type);
	}
private:

	std::unordered_map<Planttype, plantinfo> plant_infos;
};

