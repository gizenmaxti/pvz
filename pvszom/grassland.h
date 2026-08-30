#pragma once
#include<vector>
#include<optional>
#include"plantinfo.h"
#include"plant_registry.h"
class plant {
public:
	plant(Planttype rt) :t(rt),hp(plant_registry::instance().get_plant_info(t).inithp),value(plant_registry::instance().get_plant_info(t).value) {
	}
	Planttype gettype() {
		return t;
	}
	int gethp() {
		return hp;
	}
	int getvalue() {
		return value;
	}
	
private:
	Planttype t;
	int hp,value;
};

class grassland {
public:
	grassland(int row = 5, int col = 9):row(row),col(col) {
		land.resize(row,std::vector<std::optional<plant>>(col));
	}
	void planting(int row,int col,Planttype t);
	void remove(int row, int col);
	void update();
	int row, col;

private:
	std::vector<std::vector<std::optional<plant>>>land;
};