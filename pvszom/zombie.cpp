//#include<chrono>
//#include<vector>
//#include<iostream>
//#include"tool.h"
//#include "zombie.h"
//#include "plants.h"
//
//std::vector<zoms> allzombie;
//std::vector<zombie>typezombie;
//int zombiecnt = 0;
//int nowframe = 0;
//
//int zn=20;
//void putzombie() {
//	if (framecount < 60)return;
//	zoms z;
//	bool putz = false;
//	if(framecount==60) {
//		z.type = 4;
//		putz = true;
//	}
//	if(framecount>500&&framecount-nowframe-300-rand()%300>100) {
//		int type = rand() % 100;
//		if (type >= 0 && type < 60)z.type = 0;
//		else if (type >= 60 && type < 85)z.type = 2;
//		else if (type >= 85 && type < 97)z.type = 1;
//		else if (type >= 97 && type <= 100)z.type = 3;
//		putz = true;
//		nowframe = framecount;
//	}
//	if (putz) {
//		z.hp = typezombie[z.type].hp;
//		z.isEating = false;
//		z.row = rand() % 5;
//		z.x = 1000;
//		z.zy = 105 * z.row;
//		allzombie.push_back(z);
//	}
//}
//
////void putzombie(int time) {
////	static int t = 0,c=0,k=1000,cnt=0;
////	zoms z;
////	z.hp = typezombie[type].hp;
////	z.isEating = false;
////	z.row = rand() % 5;
////	z.isEating = false;
////	z.x = 1000;
////	z.zy = 105 * z.row;
////	if (time == 60) {
////		z.type = 4;
////		allzombie.push_back(z);
////	}
////	if (time > 200&&time>(t + c)&&time<200000) {
////		if (type >= 0 && type < 60)type = 0;
////		else if (type >= 60 && type < 85)type = 2;
////		else if (type >= 85 && type < 97)type = 1;
////		else if (type >= 97 && type <= 100)type = 3;
////		z.type = type;
////		allzombie.push_back(z);
////		t = time;
////		c = rand() % k;
////	}
////	cnt++;
////	if (k > 200 && cnt == 3) {
////		k--;
////		cnt = 0;
////	}
////
////}
//
//void loadzombie() {
//	int sum = countfiles("res\\images\\zombies\\zombiecard");
//	typezombie.reserve(sum);
//	for (int i = 0; i < 5; ++i) {
//		zombie z;
//		if (i == 1)z.hp = 100;
//		else if(i==2)z.hp=200;
//		else if (i == 3) {
//			z.hp = 500;
//			z.speed = 1;
//		}
//		else if (i == 4 || i==0)z.hp = 100;
//		std::string walkpath = "res\\images\\zombies\\zombie (" + std::to_string(i) + ")\\walk";
//		std::string eatpath = "res\\images\\zombies\\zombie (" + std::to_string(i) + ")\\eat";
//		for (int j = 0; j < countfiles(walkpath); ++j) {
//			IMAGE img;
//			std::string filepath = walkpath + "\\" + std::to_string(j) + ".png";
//			loadimage(&img, filepath.c_str());
//			z.walk.push_back(img);
//		}
//		for (int j = 0; j < countfiles(eatpath); ++j) {
//			IMAGE img;
//			std::string filepath = eatpath + "\\" + std::to_string(j) + ".png";
//			loadimage(&img, filepath.c_str());
//			z.eat.push_back(img);
//		}
//		typezombie.push_back(z);
//	}
//}
//
//void zoms::walking(int alpha) {
//	auto now = std::chrono::steady_clock::now();
//	float elapsed = std::chrono::duration<float>(now - lastframe).count();
//	if (elapsed >= 0.1f) {
//		walkcurrentframe = (walkcurrentframe + 1) % typezombie[type].walk.size();
//		lastframe = now;
//	}
//	putimagePNG(x-100, zy+25, &typezombie[type].walk[walkcurrentframe], alpha);
//	x -= typezombie[type].speed;
//}
//
//
//void zoms::eating(int alpha) {
//	auto now = std::chrono::steady_clock::now();
//	float elapsed = std::chrono::duration<float>(now - lastframe).count();
//	if (elapsed >= 0.1f) {
//		eatcurrentframe = (eatcurrentframe + 1) % typezombie[type].eat.size();
//		lastframe = now;
//	}
//	putimagePNG(x-100, zy+25, &typezombie[type].eat[eatcurrentframe], alpha);
//}
//void zoms::move() {
//	if (isEating) {
//		eating(255);
//	}
//	else {
//		walking(255);
//	}
//}
