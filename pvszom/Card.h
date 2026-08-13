#pragma once
#include<easyx.h>
#include<vector>
#include<string>

struct Card {
	Card(int val, int xpos, int ypos, const std::string& path, int w = 0, int h = 0) : value(val), x(xpos), y(ypos) {
		loadimage(&img, path.c_str(),w,h);
	}
	IMAGE img;
	int value;
	int x, y;
};
extern std::vector<Card> cards;
