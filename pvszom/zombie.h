#pragma once
#include <string>
#include <vector>

struct zombie {
	int hp;
	int type=0;
	int attack=20;
	float speed=0.3;
	int row;
	float x = 850, y = 100;
	bool isEating=false;
	std::vector<IMAGE> walk;
	std::vector<IMAGE> eat;
	void walking();
	void eating();
	void move();
};

struct zoms {
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	int currentframe = 0;
	zombie *z=nullptr;
	int hp;
	bool isEating;
	int row;
	float x, y;
	void walking();
	void eating();
	void move();
};
extern std::vector<zoms>allzombie;
extern std::vector<zombie>typezombie;
void loadzombie();
void putzombie(int time);
//zombie initzombie(int hp, int type, int attack, float speed, float x, float y);
