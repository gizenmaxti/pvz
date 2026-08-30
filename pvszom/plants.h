//#pragma once
//#include <chrono>
//#include <string>
//#include <vector>
////#include "graphics.h"
//#include "game.h"
//#include "tool.h"
//
//struct plant {
//	int currentframe = 0;
//	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
//	IMAGE cardimg;
//	bool isslected = false;
//	int type;
//	int hp = 100;
//	std::vector<IMAGE> dance;
//	//IMAGE bullet;
//	void dancing(int x, int y, int elp);
//	int value;
//	int damage = 0;
//	std::vector<IMAGE> bullet;
//	//void attacking(int x,int y,int t);
//};
//
//struct bullet {
//	float x=0, y=0;
//	float speed=0;
//	int damage=0;
//	bool active=false;
//	int type;
//	IMAGE img;
//	int frame=0;
//};
//
//struct plantconfig {
//	int hp;
//	int value;
//	int damage;
//	std::vector<IMAGE> dance;
//	std::vector<IMAGE> bullet;
//};
//
//struct grassmap {
//	int type=0;
//	int x, y;
//	int hp;
//	int ti = 0;
//	bool isAttacking = false;
//	int plframe = 0;
//	bool addsun = false;
//	int ra = 0;
//	bool isShooting = false;
//};
//
////struct Sun {
////	float x, y;
////	float vy;
////	bool active;
////	std::chrono::steady_clock::time_point birthTime;
////};
//
//extern std::vector<plantconfig> plantconfigs;
//extern std::vector<bullet> bullets;
//extern plant suns;  
//extern grassmap smap[5][9];
//extern std::vector<plant> plantcards;
//void loadplantcard();
//void drawcard();
//void updataglass();
//extern int framecount;
//extern void updatebllet();
//extern void drop_the_sun();
//extern int  suncount,mousey, mousex;
//extern bool isbuttondown;
