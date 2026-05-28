#include <string>
#include <vector>
#include <easyx.h>
#include "plants.h"
#include"tool.h"
//
//plant initplant(int type,int hp = 100) {
//	plant p;
//	p.type = type;
//	p.hp = hp;
//	std::string dancepath = "res/images/plant (" + std::to_string(type)+")";
//	for(int i=0;i<countfiles(dancepath);++i) {
//		IMAGE img;
//		std::string filepath = dancepath + "/" + std::to_string(i) + ".png";
//		loadimage(&img, filepath.c_str());
//		p.dance.push_back(img);
//	}
//	std::string bullet = "res/images/plants/plant ((" + std::to_string(type) + ")/bullet ";
//
//	return p;
//}
//
//void loadplantcard() {
//	for (int i = 0; i < 8; ++i) {
//		std::string filepath = "res\images\cards\card (" + std::to_string(i) + ").png";
//		loadimage(&plantcard[i], filepath.c_str(), 63, 88);
//	}
//}

//void drowcard() {
//	std::string cardpath = "res/images/cards";
//	for (int i = 0; i < 8; ++i) {
//		putimagePNG(250 + i * 70, 5,&plantcard[i]);
//	}
//}

////void plant::dancing(int x,int y,int elp=255) {
////	auto now = std::chrono::steady_clock::now();
////	float elapsed = std::chrono::duration<float>(now - lastframe).count();
////	if (elapsed >= 0.1f) {
////		currentframe = (currentframe + 1) % dance.size();
////		lastframe = now;
////	}
////	putimagePNG(x, y, &dance[currentframe], elp);
////}
////
////
////void updataglass() {
////	for(int i=0;i<5;++i) {
////		for(int j=0;j<9;++j) {
////			if(smap[i][j].pla.hp>0) {
////				smap[i][j].pla.dancing(smap[i][j].x,smap[i][j].y);
////			}
////		}
////	}
////}