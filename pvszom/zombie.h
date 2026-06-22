#pragma once
#include <string>
#include <vector>


struct zombie {
	int hp;
	int type=0;
	int attack=20;
	float speed=0.3;
	int row;
	float x = 1000, y = 100;
	bool isEating=false;
	std::vector<IMAGE> walk;
	std::vector<IMAGE> eat;
	void walking(int alpha);
	void eating(int alpha);
	void move();
};

struct zoms {
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	int walkcurrentframe = 0;
	int eatcurrentframe = 0;
	int hp;
	bool isEating;
	int row;
	float x, zy;
	void walking(int color);
	void eating(int color);
	void move();
	void debuffmove();
	int type=0;
};
extern std::vector<zoms>allzombie;
extern std::vector<zombie>typezombie;
void loadzombie();
void putzombie(int time);
