#pragma once
#include"levelinfo.h"
class level_registry {
public:
	static level_registry& instance() {
		static level_registry instance;
		return instance;
	}
	void putconfig(level l, levelinfo li) {
		levelinfos.emplace(l, std::move(li));
		levels.push_back(l);
	}
	void load();
	const std::vector<level>& getlevels() {
		return levels;
	}
	const levelinfo& get_levelinfo(level l) {
		return levelinfos.at(l);
	}
private:
	std::unordered_map<level, levelinfo>levelinfos;
	std::vector<level>levels;
};