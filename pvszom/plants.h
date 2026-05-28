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
	int hp;
	bool isAttacking = false;
	std::vector<IMAGE> dance;
	//IMAGE bullet;
	void dancing(int x,int y,int elp);
	int value;
	std::vector<IMAGE> bullet;
};

struct grassmap {
	plant *pla=nullptr;
	int x, y;
	int hp;
};
//extern std::vector<IMAGE> sun;
extern grassmap smap[5][9];
extern std::vector<plant> plantcards;
void loadplantcard();
void drawcard();
void updataglass();
