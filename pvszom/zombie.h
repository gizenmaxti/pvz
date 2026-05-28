#pragma once
#include <string>

struct zombie {
	int currentframe = 0;
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	int hp;
	int type;
	int attack;
	float speed;
	int row = rand() % 5;
	float x = 800, y = 100;
	bool isEating;
	std::vector<IMAGE> walk;
	std::vector<IMAGE> eat;
	void walking();
	void eating();
	void move();
};

zombie initzombie(int hp, int type, int attack, float speed, float x, float y);
