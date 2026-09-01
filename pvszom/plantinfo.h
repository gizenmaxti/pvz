#pragma once
#include <easyx.h>
#include<string>
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

struct plantinfo {
    plantinfo(int hp, int val, int coold, std::string n, std::string cardpath, std::string imgpath, int w, int h,
        bool canshoot = false, int damage = 0, std::string bulletpath = "")
        : inithp(hp), value(val), cooldown(coold), name(n), w(w), h(h), canshoot(canshoot), damage(damage) {
        int imgcount = countfiles(imgpath);
        patimgs.resize(imgcount);
        for (int i = 0; i < imgcount; ++i)
            loadimage(&patimgs[i], (imgpath + "\\" + std::to_string(i) + ".png").c_str(), w, h);
        loadimage(&cardimg, cardpath.c_str(), w, h);

        if (!bulletpath.empty()) {
            if (bulletpath.find(".png") != std::string::npos) {
                // 单张图片（豌豆、冰冻这种）
                bulletimgs.resize(1);
                loadimage(&bulletimgs[0], bulletpath.c_str());
            }
            else {
                // 文件夹形式（火焰豌豆这种带动画的）
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
    std::string name;
    bool canshoot;
    int damage;
    std::vector<IMAGE> bulletimgs; // 新增
};