#include <string>
#include <vector>
#include <easyx.h>
#include "plants.h"
#include"tool.h"
#include "zombie.h"
#include <iostream>

std::vector<plantconfig> plantconfigs;
 std::vector<plant> plantcards;
 std::vector<bullet> bullets;
 grassmap smap[5][9];
//void loadplantcard() {
//	plantcards.reserve(8);
//	for (int i = 0; i < 8; ++i) {
//		plant p;
//		p.hp = 100;
//		p.type = i;
//		std::string filepath = "res\\images\\cards\\(" + std::to_string(i) + ").png";
//		loadimage(&p.cardimg, filepath.c_str(), 63, 88);
//		int n = countfiles("res\\images\\plants\\plant (" + std::to_string(i) + ")");
//		p.dance.reserve(n);
//		for(int j=0;j<n;++j) {
//			IMAGE img;
//			std::string dancepath = "res\\images\\plants\\plant (" + std::to_string(i) + ")\\" + std::to_string(j) + ".png";
//			loadimage(&img, dancepath.c_str());
//			p.dance.push_back(img);
//		}
//		int nb = countfiles("res\\images\\plants\\plant (" + std::to_string(i) + ")\\bullet");
//		p.bullet.reserve(nb);
//		for (int j = 0; j < nb; ++j) {
//			IMAGE img;
//			std::string bulletpath = "res\\images\\plants\\plant (" + std::to_string(i) + ")\\bullet\\" + std::to_string(j) + ".png";
//			loadimage(&img, bulletpath.c_str());
//			p.bullet.push_back(img);
//		}
//		if (i == 0) {
//			p.value = 25;
//		}
//		if (i == 1) {
//			p.value = 200;
//		}
//		if (i == 2) {
//			p.value = 50;
//		}
//		if (i == 3) {
//			p.value = 50;
//		}
//		if (i == 4) {
//			p.value = 50;
//			p.hp = 1000;
//		}
//		if (i == 5) {
//			p.value = 175;
//		}
//		if (i == 6) {
//			p.value = 150;
//		}
//		if (i == 7) {
//			p.value = 100;
//		}
//		plantcards.push_back(p);
//	}
//}

 IMAGE loadcardpath(std::string filepath, int w = 0, int h = 0) {
	 IMAGE img;
	 loadimage(&img, filepath.c_str(), w, h);
	 return img;
 }

 std::vector<IMAGE> loaddancepath(std::string folderpath) {
	 std::vector<IMAGE> dance;
	 int n = countfiles(folderpath);
	 dance.reserve(n);
	 for (int j = 0; j < n; ++j) {
		 IMAGE img;
		 std::string dancepath = folderpath + "\\" + std::to_string(j) + ".png";
		 loadimage(&img, dancepath.c_str());
		 dance.push_back(img);
	 }
	 return dance;
 }

 plant initplant(int type, int hp, int value, int currentframe, int damage, bool isslected) {
	 plant p;
	 p.type = type;
	 p.hp = hp;
	 p.value = value;
	 p.currentframe = currentframe;
	 p.damage = damage;
	 p.isslected = isslected;
	 p.lastframe = std::chrono::steady_clock::now();

	 p.cardimg = loadcardpath("res\\images\\cards\\(" + std::to_string(type) + ").png", 63, 88);

	 p.dance = loaddancepath("res\\images\\plants\\plant (" + std::to_string(type) + ")");

	 p.bullet = loaddancepath("res\\images\\plants\\plant (" + std::to_string(type) + ")\\bullet");

	 return p;
 }

 void loadplantcard() {
		
	 plantcards.reserve(8);
	 for (int i = 0; i < 8; ++i) {
		 plant p;
		 
		 if (i == 0) {
			 p=initplant(0, 100, 25, 0, 500, false);
		 }
		 else if (i == 1) {
			 p=initplant(1, 100, 200, 10, 0, false);
		 }
		 else if (i == 2) {
			 p=initplant(2, 100, 50, 0, 0, false);
		 }
		 else if (i == 3) {
			 p=initplant(3, 100, 50, 0, 0, false);
		 }
		 else if (i == 4) {
			 p=initplant(4, 1000, 50, 0, 0, false);
		 }
		 else if (i == 5) {
			 p=initplant(5, 100, 175, 0, 0, false);
		 }
		 else if (i == 6) {
			 p=initplant(6, 100, 150, 0, 0, false);
		 }
		 else if (i == 7) {
			 p=initplant(7, 100, 100, 0, 0, false);
		 }
		 plantcards.push_back(p);
	 }
 }

void drawcard() {
	for (int i = 0; i < 8; ++i) {
		putimage(250 + i * 70, 5,&plantcards[i].cardimg);
	}
}


void plant::dancing(int x,int y,int elp=255) {
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - lastframe).count();
	if (elapsed >= 0.1f) {
		currentframe = (currentframe + 1) % dance.size();
		lastframe = now;
	}
	putimagePNG(x, y, &dance[currentframe], elp);
}

void updatebllet() {
	for(auto it=bullets.begin();it!=bullets.end();) {
		if(it->active) {
			putimagePNG(it->x, it->y, &it->img, 255);
			it->x += it->speed;
			++it;
		}
		else {
			it=bullets.erase(it);
		}
	}
}


//void plant_potato_attacking(grassmap *p) { //土豆地雷 植物0 
//	b.x = p->x * 80 + 200;
//	b.y = p->y * 100 + 90;
//	b.active = true;
//	b.img = plantcards[0].bullet[0];
//	b.damage = 500;
//	b.type = 0;
//	bullets.push_back(b);
//	p->hp = 0;
//	std::cout << "Potato Mine exploded at (" << p->x << ", " << p->y << ")" << std::endl;
//}

void updapalntdance(grassmap p) {
	if (p.type == 3) {
		plantcards[p.type].dancing(p.x * 82 + 150, p.y * 100 - 70, 255);
	}else
		plantcards[p.type].dancing(p.x * 80 + 165, p.y * 100 + 90, 255);
}


bullet addbullet(grassmap p) {
	bullet b;
	b.active = true;
	b.damage = plantcards[p.type].damage;
	b.img = plantcards[p.type].bullet[0];
	b.type = p.type;
	b.x = p.x * 80 + 200;
	b.y = p.y * 100 + 90;
	return b;
}

void updataglass() {
	for(int i=0;i<5;++i) {
		for(int j=0;j<9;++j) {
			if(smap[i][j].hp>0) {
				updapalntdance(smap[i][j]);
				if (smap[i][j].isAttacking) {
					//if (smap[i][j].type == 0)plant_potato_attacking(&smap[i][j]);
					if (smap[i][j].type == 0) {
						smap[i][j].hp = 0;
						putimagePNG(smap[i][j].x * 80 + 165, smap[i][j].y * 100 + 90, &plantcards[smap[i][j].type].bullet[0], 255);
					}
					if (smap[i][j].type == 1) {
						if(framecount%100==0) {
							bullets.push_back(addbullet(smap[i][j]));
						}
					}
				}
				//if (smap[i][j].type == 2) {
				//	smap[i][j].plframe = (smap[i][j].plframe + 1) % plantcards[smap[i][j].type].bullet.size();
				//	if (smap[i][j].addsun) {
				//		putimagePNG(smap[i][j].x * 80 + 165, smap[i][j].y * 100 + 90, &plantcards[smap[i][j].type].bullet[smap[i][j].plframe], 255);
				//		//smap[i][j].addsun = false;
				//	}
				//	smap[i][j].ti=(smap[i][j].ti+1)%1000;
				//	if (smap[i][j].ti == 200)smap[i][j].addsun = true;
				//	if(smap[i][j].ti>800)smap[i][j].addsun = false;
				//}

				//if (smap[i][j].type == 6) {
				//	if (smap[i][j].plframe > 20) {
				//		if (smap[i][j].plframe > 60)smap[i][j].hp -= 100;
				//		putimagePNG(smap[i][j].x * 80 + 165, smap[i][j].y * 100 + 90, &plantcards[smap[i][j].type].bullet[0], 255);
				//	}
				//	smap[i][j].plframe++;
				//}

				//if (smap[i][j].isAttacking && i >= 0 && i < 5 && j >= 0 && j < 9) {
				//	if (smap[i][j].type==0&&smap[i][j].ti < 10) {
				//		putimagePNG(smap[i][j].x * 80 + 165, smap[i][j].y * 100 + 90, &plantcards[smap[i][j].type].bullet[0], 255);
				//		smap[i][j].ti ++;
				//	}
				//	else if (smap[i][j].type == 0) {
				//		smap[i][j].hp = 0;
				//	}
				//	bullet b;
				//	b.x = smap[i][j].x * 80 + 200;
				//	b.y = smap[i][j].y * 100 + 90;
				//	b.active = true;
				//	b.img = plantcards[smap[i][j].type].bullet[0];
				//	b.damage = 20;
				//	b.speed = 10;
				//	b.type = smap[i][j].type;
				//	if (smap[i][j].type == 1) {
				//		if(framecount%100==0) {
				//			bullets.push_back(b);
				//		}
				//		if (framecount % 101 == 0) {
				//			bullets.push_back(b);
				//		}
				//	}
				//	if (smap[i][j].type == 5 || smap[i][j].type == 7) {
				//		if (framecount % 100 == 0) {
				//			bullets.push_back(b);
				//		}
				//	}
				//}
			}
		}
	}
}