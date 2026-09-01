#pragma once
#include <easyx.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "zombie_type.h"
#include "tool.h"

struct zombieinfo {
    zombieinfo(int hp, float speed, int attack, std::string walkpath, std::string eatpath, int w, int h)
        : inithp(hp), speed(speed), attack(attack), w(w), h(h) {
        int wc = countfiles(walkpath);
        walkimgs.resize(wc);
        for (int i = 0; i < wc; ++i)
            loadimage(&walkimgs[i], (walkpath + "\\" + std::to_string(i) + ".png").c_str(), w, h);

        int ec = countfiles(eatpath);
        eatimgs.resize(ec);
        for (int i = 0; i < ec; ++i)
            loadimage(&eatimgs[i], (eatpath + "\\" + std::to_string(i) + ".png").c_str(), w, h);
    }
    int inithp;
    float speed;
    int attack;
    int w, h;
    std::vector<IMAGE> walkimgs;
    std::vector<IMAGE> eatimgs;
};

class zombie_registry {
public:
    static zombie_registry& instance() {
        static zombie_registry inst;
        return inst;
    }
    void putconfig(Zombietype t, zombieinfo z) { infos.emplace(t, z); }
    void load();
    const zombieinfo& get_zombie_info(Zombietype t) const { return infos.at(t); }
private:
    std::unordered_map<Zombietype, zombieinfo> infos;
};