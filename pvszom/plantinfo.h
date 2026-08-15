#pragma once
#include <easyx.h>
#include<string>
#include"plant_type.h";
#include"input.h"

struct plantinfo {
	plantinfo(int hp, int val, int coold, std::string n, std::string cardpath, std::string plantpath,int w,int h) :
		inithp(hp),value(val),cooldown(coold),w(w),h(h) {
		loadimage(&cardimg, cardpath.c_str(),w,h);
		loadimage(&plantimg, plantpath.c_str(),w,h);
	};
	bool hittest() {
		return x>=msgx&&msgx<=x+w&&y<msgy&&msgy>y+h&&clicked;
	};
	int inithp;
	int value;
	int cooldown;
	int w, h;
	IMAGE cardimg;
	IMAGE plantimg;
	std::string name;
	int x, y;
};

