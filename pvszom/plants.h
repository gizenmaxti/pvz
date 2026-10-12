#pragma once
#include <memory>
#include "plant_base.h"
#include "plant_registry.h"
#include "zombie.h"

// 场地的列宽与行高（与 grassland / battle_manager 的布局保持一致）
constexpr float kCellW = 80.0f;
constexpr float kCellH = 100.0f;
constexpr float kFieldLeft = 170.0f;
constexpr float kFieldTop = 90.0f;

// 该行、该列右侧是否还有活着的僵尸（用于判断要不要开火）
inline bool zombieAheadInRow(const BattleContext& ctx, int row, int col) {
    if (!ctx.zombies) return false;
    const float threshold = kFieldLeft + static_cast<float>(col) * kCellW;
    for (const auto& z : *ctx.zombies) {
        if (z.getrow() == row && z.gethp() > 0 && z.getx() > threshold) return true;
    }
    return false;
}

// 射手通用逻辑：冷却到点且右方有僵尸时，标记本帧开火。
// 子类只负责决定"发射几颗、什么弹种"，不必重复计时逻辑。
class ShooterPlant : public plant {
public:
    using plant::plant;

    void onTick(float deltaTime, BattleContext& ctx) override {
        attackTimer += deltaTime;
        if (attackTimer < attackInterval) return;
        if (!zombieAheadInRow(ctx, gridRow, gridCol)) return;

        attackTimer -= attackInterval;
        onFire(ctx);
    }

    void setGrid(int row, int col) { gridRow = row; gridCol = col; }

protected:
    // 子类实现：本帧发射什么
    virtual void onFire(BattleContext& ctx) = 0;

    float bulletX() const { return kFieldLeft + static_cast<float>(gridCol) * kCellW + 60.0f; }
    float bulletY() const { return kFieldTop + static_cast<float>(gridRow) * kCellH + 40.0f; }

    int gridRow = 0;
    int gridCol = 0;
};

// 豌豆射手：单发普通豌豆
class PeashooterPlant : public ShooterPlant {
public:
    using ShooterPlant::ShooterPlant;
protected:
    void onFire(BattleContext& ctx) override {
        if (ctx.spawnBullet)
            ctx.spawnBullet(bulletX(), bulletY(), gridRow, getDamage(), &getBulletImg(), false);
    }
};

// 双发射手：一次射出两颗豌豆，第二颗稍后一点射出，避免完全重叠
class DoubleShooterPlant : public ShooterPlant {
public:
    using ShooterPlant::ShooterPlant;

    void onTick(float deltaTime, BattleContext& ctx) override {
        ShooterPlant::onTick(deltaTime, ctx);
        if (pendingSecond > 0) {
            pendingSecond -= deltaTime;
            if (pendingSecond <= 0.0f) {
                if (ctx.spawnBullet)
                    ctx.spawnBullet(bulletX() + 18.0f, bulletY(), gridRow, getDamage(), &getBulletImg(), false);
                pendingSecond = 0.0f;
            }
        }
    }

protected:
    void onFire(BattleContext& ctx) override {
        if (ctx.spawnBullet)
            ctx.spawnBullet(bulletX(), bulletY(), gridRow, getDamage(), &getBulletImg(), false);
        pendingSecond = 0.12f;   // 第二颗延后 0.12 秒
    }

private:
    float pendingSecond = 0.0f;
};

// 机枪射手：射速极快（间隔由配置给出）
class MachineGunPlant : public ShooterPlant {
public:
    using ShooterPlant::ShooterPlant;
protected:
    void onFire(BattleContext& ctx) override {
        if (ctx.spawnBullet)
            ctx.spawnBullet(bulletX(), bulletY(), gridRow, getDamage(), &getBulletImg(), false);
    }
};

// 寒冰射手：命中后使僵尸减速（由子弹的 ice 标记触发）
class IceShooterPlant : public ShooterPlant {
public:
    using ShooterPlant::ShooterPlant;
protected:
    void onFire(BattleContext& ctx) override {
        if (ctx.spawnBullet)
            ctx.spawnBullet(bulletX(), bulletY(), gridRow, getDamage(), &getBulletImg(), true);
    }
};

// 向日葵：周期性产出阳光，产出瞬间切换到攻击动画
class SunflowerPlant : public plant {
public:
    using plant::plant;

    void setGrid(int, int) {}

    void onTick(float deltaTime, BattleContext& ctx) override {
        sunTimer += deltaTime;
        if (sunTimer >= sunInterval) {
            sunTimer -= sunInterval;
            sunProducing = true;
            produceTimer = 0.6f;            // 播放一小段产出动画
            if (ctx.spawnSun) ctx.spawnSun();
        }
        if (sunProducing) {
            produceTimer -= deltaTime;
            if (produceTimer <= 0.0f) sunProducing = false;
        }
    }

    // 产出时播攻击动画，平时播待机动画
    const IMAGE& dance() const override {
        if (sunProducing) {
            const auto& imgs = plant_registry::instance().get_plant_info(gettype()).attackimgs;
            return frameOf(imgs, frameCounter());
        }
        return plant::dance();
    }

private:
    int frameCounter() const { return static_cast<int>(sunTimer / kAnimFrameTime); }

    float sunTimer = 0.0f;
    float sunInterval = 12.0f;   // 每 12 秒产一次阳光
    float produceTimer = 0.0f;
    bool sunProducing = false;
};

// 坚果墙：高血量、不攻击，主要用于阻挡
class NutsPlant : public plant {
public:
    using plant::plant;
    void setGrid(int, int) {}
};

// 树桩：低血量、不攻击
class TreeStumpPlant : public plant {
public:
    using plant::plant;
    void setGrid(int, int) {}
};

// 土豆雷：不攻击（爆炸行为尚未实现，先按静态植物处理）
class PotatoPlant : public plant {
public:
    using plant::plant;
    void setGrid(int, int) {}
};
