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

struct bullet {
	float x, y;
	float speed=10;
	int damage;
	bool active;
	int type;
	IMAGE img;
};

struct grassmap {
	int type=0;
	int x, y;
	int hp;
	int ti = 0;
	bool isAttacking = false;
	int plframe = 0;
	bool addsun = false;
	float bulletx=0;
	int ra = rand();
	bool isShooting = false;
};

//struct Sun {
//	float x, y;
//	float vy;
//	bool active;
//	std::chrono::steady_clock::time_point birthTime;
//};

extern std::vector<bullet> bullets;
extern plant suns;  
extern grassmap smap[5][9];
extern std::vector<plant> plantcards;
void loadplantcard();
void drawcard();
void updataglass();
extern int framecount;
extern void updatebllet();
