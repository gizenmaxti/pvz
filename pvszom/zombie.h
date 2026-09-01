#pragma once
#include <chrono>
#include "zombie_registry.h"

class zombie {
public:
    zombie(Zombietype zt, int row)
        : t(zt), row(row), hp(zombie_registry::instance().get_zombie_info(zt).inithp), x(900.0f) {
    }

    void move(float deltaTime) {
        x -= zombie_registry::instance().get_zombie_info(t).speed * deltaTime;
    }

    const IMAGE& anim(bool eating) {
        auto& imgs = eating ? zombie_registry::instance().get_zombie_info(t).eatimgs
            : zombie_registry::instance().get_zombie_info(t).walkimgs;
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration<float>(now - lastframe).count() > 0.15f) {
            curframe = (curframe + 1) % imgs.size();
            lastframe = now;
        }
        return imgs[curframe];
    }

    int gethp() const { return hp; }
    void takeDamage(int dmg) { hp -= dmg; }
    float getx() const { return x; }
    int getrow() const { return row; }
    int getattack() const { return zombie_registry::instance().get_zombie_info(t).attack; }

private:
    Zombietype t;
    int row;
    float x;
    int hp;
    int curframe = 0;
    std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
};