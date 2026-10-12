#pragma once
#include <chrono>
#include "zombie_registry.h"
#include "battle_context.h"

class zombie {
public:
    zombie(Zombietype zt, int row)
        : t(zt), row(row), hp(zombie_registry::instance().get_zombie_info(zt).inithp), x(900.0f) {
    }

    void move(float deltaTime) {
        // 冰冻状态下移速减半；减速剩余时间在这里递减
        if (slowTimer > 0.0f) {
            slowTimer -= deltaTime;
            if (slowTimer < 0.0f) slowTimer = 0.0f;
        }
        const float factor = isSlowed() ? 0.5f : 1.0f;
        x -= zombie_registry::instance().get_zombie_info(t).speed * factor * deltaTime;
    }

    // 寒冰射手命中效果：减速一段时间（重复命中则刷新）
    void applySlow(float duration) { if (duration > slowTimer) slowTimer = duration; }
    bool isSlowed() const { return slowTimer > 0.0f; }

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
    float slowTimer = 0.0f;   // >0 表示处于冰冻减速中
    std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
};