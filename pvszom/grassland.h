#pragma once
#include<vector>
#include<optional>
#include"plant.h"
class grassland {
public:
	grassland(int row = 5, int col = 9) :row(row), col(col) {
		land.resize(row, std::vector<std::optional<plant>>(col));
	}
	bool planting(int row, int col, Planttype t, int suncount);
	void remove(int row, int col);
	void update();
	plant* getPlant(int row, int col);
	void damagePlant(int row, int col, int dmg);
	int row, col;

private:
	std::vector<std::vector<std::optional<plant>>>land;
};