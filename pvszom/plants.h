#pragma once
#include <chrono>
#include <string>
#include <vector>
#include "graphics.h"
struct plant {
	int currentframe = 0;
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	IMAGE cardimg;
	bool isslected = false;
	int type;
	int hp=100;
	std::vector<IMAGE> dance;
	//IMAGE bullet;
	void dancing(int x,int y,int elp);
	int value;
	std::vector<IMAGE> bullet;
	void attacking(int x,int y,int t);
};

struct grassmap {
	int type=0;
	int x, y;
	int hp;
	int ti = 0;
	bool isAttacking = false;
	int plframe = 0;
	bool addsun = false;
	float distance = 9999;
};
extern grassmap smap[5][9];
extern std::vector<plant> plantcards;
void loadplantcard();
void drawcard();
void updataglass();
