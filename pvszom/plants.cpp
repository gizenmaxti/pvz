#include <string>
#include <vector>
#include <easyx.h>
#include "plants.h"
#include"tool.h"

 std::vector<plant> plantcards;
 grassmap smap[5][9];
//plant initplant(int type,int hp = 100) {
//	plant p;
//	p.type = type;
//	p.hp = hp;
//	std::string dancepath = "res/images/plant (" + std::to_string(type)+")";
	/*for(int i=0;i<countfiles(dancepath);++i) {
		IMAGE img;
		std::string filepath = dancepath + "/" + std::to_string(i) + ".png";
		loadimage(&img, filepath.c_str());
		p.dance.push_back(img);
	}*/
//	std::string bullet = "res/images/plants/plant ((" + std::to_string(type) + ")/bullet ";
//
//	return p;
//}
//
void loadplantcard() {
	plantcards.reserve(8);
	for (int i = 0; i < 8; ++i) {
		plant p;
		p.hp = 100;
		p.type = i;
		std::string filepath = "res\\images\\cards\\(" + std::to_string(i) + ").png";
		loadimage(&p.cardimg, filepath.c_str(), 63, 88);
		int n = countfiles("res\\images\\plants\\plant (" + std::to_string(i) + ")");
		p.dance.reserve(n);
		for(int j=0;j<n;++j) {
			IMAGE img;
			std::string dancepath = "res\\images\\plants\\plant (" + std::to_string(i) + ")\\" + std::to_string(j) + ".png";
			loadimage(&img, dancepath.c_str());
			p.dance.push_back(img);
		}
		/*std::string bulletn = "res\\images\\plants\\plant (" + std::to_string(i) + ")\\bullet\\bullet.png";
		loadimage(&p.bullet, bulletn.c_str(), 63, 88);*/
		int nb = countfiles("res\\images\\plants\\plant (" + std::to_string(i) + ")\\bullet");
		p.bullet.reserve(nb);
		for (int j = 0; j < nb; ++j) {
			IMAGE img;
			std::string bulletpath = "res\\images\\plants\\plant (" + std::to_string(i) + ")\\bullet\\" + std::to_string(j) + ".png";
			loadimage(&img, bulletpath.c_str());
			p.bullet.push_back(img);
		}
		if (i == 0) {
			p.value = 25;
		}
		if (i == 1) {
			p.value = 200;
		}
		if (i == 2) {
			p.value = 50;
		}
		if (i == 3) {
			p.value = 50;
		}
		if (i == 4) {
			p.value = 50;
			p.hp = 1000;
		}
		if (i == 5) {
			p.value = 175;
		}
		if (i == 6) {
			p.value = 150;
		}
		if (i == 7) {
			p.value = 100;
		}
		plantcards.push_back(p);
	}
	/*for (int i = 0; i < n; ++i) {
		IMAGE img;
		loadimage(&img,("res\\images\\plants\\sun\\"+std::to_string(i)+".png").c_str());
		sun.push_back(img);
	}*/
}
void sunning() {

}
void drawcard() {
	std::string cardpath = "res\\images\\cards";
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


void updataglass() {
	for(int i=0;i<5;++i) {
		for(int j=0;j<9;++j) {
			if(smap[i][j].pla.hp>0) {
				if (smap[i][j].pla.type == 3) {
					smap[i][j].pla.dancing(smap[i][j].x*82+150,smap[i][j].y*100-70,255);
				}
				else
				smap[i][j].pla.dancing(smap[i][j].x*80+165,smap[i][j].y*100+90,255);
			}
		}
	}
}