#include<chrono>
#include<vector>
#include"tool.h"
#include "zombie.h"

zombie initzombie(int hp, int type, int attack, float speed, float x, float y) {
	zombie z;
	z.hp = hp;
	z.type = type;
	z.attack = attack;
	z.speed = speed;
	z.x = x;
	z.y = y;
	std::string walkpath = "res/images/zombies/zombie (" + std::to_string(z.type) + ")/walk";
	std::string eatpath = "res/images/zombies/zombie (" + std::to_string(z.type) + ")/eat";
	for (int j = 0; j < countfiles(walkpath); ++j) {
		IMAGE img;
		std::string filepath = walkpath + "/" + std::to_string(j) + ".png";
		loadimage(&img, filepath.c_str());
		z.walk.push_back(img);
	}
	for (int j = 0; j < countfiles(eatpath); ++j) {
		IMAGE img;
		std::string filepath = eatpath + "/" + std::to_string(j) + ".png";
		loadimage(&img, filepath.c_str());
		z.eat.push_back(img);
	}
	return z;
}
void zombie::walking() {
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - lastframe).count();
	if (elapsed >= 0.1f) {
		currentframe = (currentframe + 1) % walk.size();
		lastframe = now;
	}
	putimagePNG(x, y * row, &walk[currentframe]);
	x -= speed;
}

void zombie::eating() {
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - lastframe).count();
	if (elapsed >= 0.1f) {
		currentframe = (currentframe + 1) % eat.size();
		lastframe = now;
	}
	putimagePNG(x, y * row, &eat[currentframe]);
}
void zombie::move() {
	if (isEating) {
		//walking();
		eating();
	}
	else {
		//eating();
		walking();
	}
}
