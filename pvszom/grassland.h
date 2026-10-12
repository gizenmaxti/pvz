#pragma once
#include<vector>
#include<memory>
#include"plant_base.h"
#include"plant_registry.h"

class grassland {
public:
	grassland(int row = 5, int col = 9) :row(row), col(col) {
		// 注意不能用 resize 填充：unique_ptr 只能移动不能拷贝，
		// 这里逐格构造空槽位。
		land.reserve(row);
		for (int i = 0; i < row; ++i) {
			std::vector<std::unique_ptr<plant>> line;
			line.reserve(col);
			for (int j = 0; j < col; ++j) line.push_back(nullptr);
			land.push_back(std::move(line));
		}
	}

	// 只负责"能否种下并创建植物"，不再顺带修改阳光计数（那是调用方的职责）
	bool planting(int row, int col, Planttype t, int suncount);

	void remove(int row, int col);
	void update(float deltaTime);
	void draw();

	plant* getPlant(int row, int col);
	void damagePlant(int row, int col, int dmg);

	int row, col;

private:
	// 用 unique_ptr 而非 optional<plant>：基类 plant 是多态的，
	// 值语义存储会发生对象切片，派生类的行为全部丢失。
	std::vector<std::vector<std::unique_ptr<plant>>>land;
};
