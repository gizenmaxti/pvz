#pragma once
#include<unordered_map>
#include"plantinfo.h"
#include"plant_type.h"
class plant_registry {
public:
	static plant_registry& instance() {
		static plant_registry instance;
		return instance;
	}
	void load();
	const plantinfo& get_plant_info(Planttype type) const {
		return plant_infos.at(type);
	}
private:
	std::unordered_map<Planttype, plantinfo> plant_infos;
};