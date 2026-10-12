#pragma once
#include <easyx.h>
#include <string>
#include <vector>
#include"tool.h"

enum class Planttype {
    sunflower,
    peashooter,
    potato,
    doubleshooter,
    iceshooter,
    treestump,
    machinegun,
    nuts
};

//struct plantinfo {
//	
//	/*plantinfo(int hp, int val, int coold, std::string n, std::string cardpath, std::string imgpath, int w, int h) :
//		inithp(hp), value(val), cooldown(coold), name(n), w(w), h(h) {
//		int imgcount = countfiles(imgpath);
//		patimgs.resize(imgcount);
//		for (int i = 0; i < countfiles(imgpath); ++i)loadimage(&patimgs[i], (imgpath + "//" + std::to_string(i) + ".png").c_str(), w, h);
//		loadimage(&cardimg, cardpath.c_str(), w, h);
//	};*/
//
//	plantinfo(int hp, int val, int coold, std::string n, std::string cardpath, std::string imgpath, int w, int h,
//		bool canshoot = false, int damage = 0)
//		: inithp(hp), value(val), cooldown(coold), name(n), w(w), h(h), canshoot(canshoot), damage(damage) {
//		int imgcount = countfiles(imgpath);
//		patimgs.resize(imgcount);
//		for (int i = 0; i < countfiles(imgpath); ++i)loadimage(&patimgs[i], (imgpath + "//" + std::to_string(i) + ".png").c_str(), w, h);
//		loadimage(&cardimg, cardpath.c_str(), w, h);
//
//
//	}
//
//
//	bool canshoot;
//	int damage;
//
//	int inithp;
//	int value;
//	int cooldown;
//	int w, h;
//	IMAGE cardimg;
//
//	std::vector<IMAGE>patimgs;
//	std::string name;
//	std::vector<IMAGE>bulletimgs;
//};

struct plantinfo {
    plantinfo(int hp, int val, int coold, std::string n, std::string cardpath, std::string imgpath, int w, int h,
        bool canshoot = false, int damage = 0, std::string bulletpath = "", float attackInterval = 1.5f)
        : inithp(hp), value(val), cooldown(coold), name(n), w(w), h(h), canshoot(canshoot), damage(damage),
          attackInterval(attackInterval) {
        int imgcount = countfiles(imgpath);
        patimgs.resize(imgcount);
        for (int i = 0; i < imgcount; ++i)
            loadimage(&patimgs[i], (imgpath + "\\" + std::to_string(i) + ".png").c_str(), w, h);
        loadimage(&cardimg, cardpath.c_str(), w, h);

        // 部分植物（如向日葵）带一套攻击/产出动画，存在 attack 子目录
        const int acount = countfiles(imgpath + "\\attack");
        if (acount > 0) {
            attackimgs.resize(acount);
            for (int i = 0; i < acount; ++i)
                loadimage(&attackimgs[i], (imgpath + "\\attack\\" + std::to_string(i) + ".png").c_str(), w, h);
        }

        if (!bulletpath.empty()) {
            if (bulletpath.find(".png") != std::string::npos) {
                bulletimgs.resize(1);
                loadimage(&bulletimgs[0], bulletpath.c_str());
            }
            else {
                int bc = countfiles(bulletpath);
                bulletimgs.resize(bc);
                for (int i = 0; i < bc; ++i)
                    loadimage(&bulletimgs[i], (bulletpath + "\\" + std::to_string(i) + ".png").c_str());
            }
        }
    }

    int inithp, value, cooldown, w, h;
    IMAGE cardimg;
    std::vector<IMAGE> patimgs;
    std::vector<IMAGE> attackimgs;   // 攻击/产出动画（可能为空）
    std::string name;
    bool canshoot;
    int damage;
    float attackInterval;          // 攻击间隔（秒），每个植物可不同
    std::vector<IMAGE> bulletimgs; // 新增
};