#include<chrono>
#include<vector>
#include<iostream>
#include"tool.h"
#include "zombie.h"
#include "plants.h"

std::vector<zoms> allzombie;
std::vector<zombie>typezombie;
void putzombie(int time) {
	static int t = 0,c=0,k=2000,cnt=0;
	int type = rand()%100;
	if(type>=0&&type<60)type=0;
	else if(type>=60&&type<85)type=2;
	else if(type>=85&&type<97)type=1;
	else if(type>=97&&type<=100)type=3;
	zoms z;
	if (time == 60) {
		type = 4;
	}
	z.z = &typezombie[type];
	z.hp = typezombie[type].hp;
	z.isEating = false;
	z.row = rand() % 5;
	z.isEating = false;
	z.x = 800;
	z.y = 105 * z.row;
	if (time == 60) {
		allzombie.push_back(z);
	}
	if (time > 200&&time>(t + c)&&time<20000) {
		allzombie.push_back(z);
		t = time;
		c = rand() % k;
	}
	cnt++;
	if (k > 500 && cnt == 5) {
		k--;
		cnt = 0;
	}
}

void loadzombie() {
	int sum = countfiles("res\\images\\zombies\\zombiecard");
	typezombie.reserve(sum);
	for (int i = 0; i < 5; ++i) {
		zombie z;
		if (i == 1)z.hp = 100;
		else if(i==2)z.hp=200;
		else if (i == 3) {
			z.hp = 500;
			z.speed = 1;
		}
		else if (i == 4)z.hp = 100;
		std::string walkpath = "res\\images\\zombies\\zombie (" + std::to_string(i) + ")\\walk";
		std::string eatpath = "res\\images\\zombies\\zombie (" + std::to_string(i) + ")\\eat";
		for (int j = 0; j < countfiles(walkpath); ++j) {
			IMAGE img;
			std::string filepath = walkpath + "\\" + std::to_string(j) + ".png";
			loadimage(&img, filepath.c_str());
			z.walk.push_back(img);
		}
		for (int j = 0; j < countfiles(eatpath); ++j) {
			IMAGE img;
			std::string filepath = eatpath + "\\" + std::to_string(j) + ".png";
			loadimage(&img, filepath.c_str());
			z.eat.push_back(img);
		}
		typezombie.push_back(z);
	}
}

void zoms::walking() {
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - lastframe).count();
	if (elapsed >= 0.1f) {
		currentframe = (currentframe + 1) % z->walk.size();
		lastframe = now;
	}
	putimagePNG(x, y+25, &z->walk[currentframe]);
	x -= z->speed;
}

void zoms::eating() {
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - lastframe).count();
	if (elapsed >= 0.1f) {
		currentframe = (currentframe + 1) % z->eat.size();
		lastframe = now;
	}
	putimagePNG(x, y+25, &z->eat[currentframe]);
}
void zoms::move() {
	if (isEating) {
		eating();
	}
	else {
		walking();
	}
}