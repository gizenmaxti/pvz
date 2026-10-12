#pragma once
#include <functional>
#include <vector>
#include "battle_context.h"
#include "plant_registry.h"

// 植物统一走这个位置刷新动画帧，帧率与僵尸保持一致（15 fps）。
// 原先向日葵用 10 fps、僵尸用 15 fps，视觉上不统一。
constexpr float kAnimFrameTime = 0.15f;

inline const IMAGE& frameOf(const std::vector<IMAGE>& imgs, int frame) {
    static const IMAGE empty{};
    if (imgs.empty()) return empty;          // 资源缺失时不再对 0 取模
    return imgs[static_cast<size_t>(frame) % imgs.size()];
}

// 所有植物的基类。
//
// 重构前只有一个 plant 结构体，用 Planttype 分支区分行为，导致：
//   * 无法表达"向日葵产阳光"这类个体状态（产出计时器没有地方放）；
//   * 想要新行为只能继续往 battle_manager 里加 if 分支。
// 现在改成抽象基类 + 派生类：通用部分（血量、动画、受击）留在基类，
// 个体行为（射击、产阳光、减速）由各子类实现 onTick。
class plant {
public:
    explicit plant(Planttype t) : t(t) {}

    virtual ~plant() = default;

    // 构造函数里不查注册表：注册表在 load() 时才填好，而对象在此之前就可能被创建。
    // 改为构造后由工厂统一调用，职责更清楚，也解开了头文件循环包含。
    void init() {
        const auto& info = plant_registry::instance().get_plant_info(t);
        hp = info.inithp;
        value = info.value;
        cooldown = info.cooldown;
        attackInterval = info.attackInterval;
    }

    // 每帧调用；deltaTime 为秒。子类在此实现自己的行为。
    virtual void onTick(float deltaTime, BattleContext& ctx) { (void)deltaTime; (void)ctx; }

    // 播放一帧动画并推进帧号
    virtual void updateAnimation(float deltaTime) {
        animTimer += deltaTime;
        if (animTimer >= kAnimFrameTime) {
            ++curframe;
            animTimer -= kAnimFrameTime;
        }
    }

    virtual const IMAGE& dance() const {
        return frameOf(plant_registry::instance().get_plant_info(t).patimgs, curframe);
    }

    Planttype gettype() const { return t; }
    int gethp() const { return hp; }
    int getvalue() const { return value; }
    int getcooldown() const { return cooldown; }
    int getDamage() const { return plant_registry::instance().get_plant_info(t).damage; }
    bool canAttack() const { return plant_registry::instance().get_plant_info(t).canshoot; }
    const IMAGE& getBulletImg(int frame = 0) const {
        return frameOf(plant_registry::instance().get_plant_info(t).bulletimgs, frame);
    }

    void takeDamage(int dmg) { hp -= dmg; }

protected:
    Planttype t;
    int hp = 100;
    int value = 0;
    int cooldown = 0;
    float attackInterval = 1.5f;   // 攻击间隔（秒），来自配置
    float attackTimer = 0.0f;
    int curframe = 0;
    float animTimer = 0.0f;
};
