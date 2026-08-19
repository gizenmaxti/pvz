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
	//void register_plant(Planttype type, plantinfo p) {
	//	plant_infos.emplace(type, std::move(p));
	//	//plant_types.push_back(type);
	//}
	std::unordered_map<Planttype, plantinfo> plant_infos;
	//std::vector<Planttype> plant_types;
};

