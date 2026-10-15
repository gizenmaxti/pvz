#include "battle_manager.h"
#include "plant_registry.h"
#include "plants.h"
#include "tool.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <easyx.h>

void battle_manager::init(grassland* grass, int totalZombies) {
    g = grass;
    totalToSpawn = totalZombies;
    spawnedCount = 0;
    spawnTimer = 0;
    zombies.clear();
    bullets.clear();
    result = BattleResult::ongoing;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 9; ++j)
            eatTimer[i][j] = 0;
}


void battle_manager::trySpawnZombie(float deltaTime) {
    if (spawnedCount >= totalToSpawn) return;
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        int row = rand() % 5;
        Zombietype type = Zombietype::zombie;
        int roll = rand() % 100;
        if (roll < 60) type = Zombietype::zombie;
        else if (roll < 80) type = Zombietype::loadblock;
        else if (roll < 92) type = Zombietype::iron;
        else type = Zombietype::rugby;

        zombies.emplace_back(type, row);
        spawnedCount++;
    }
}

// 植物行为统一由这里驱动：把僵尸列表和两个回调打包成 BattleContext 注入进去，
// 具体发射什么、产不产阳光由植物子类自己决定。
void battle_manager::updatePlants(float deltaTime) {
    BattleContext ctx;
    ctx.zombies = &zombies;
    ctx.spawnBullet = [this](float x, float y, int row, int damage, const void* img, bool ice) {
        bullets.emplace_back(x, y, row, damage, static_cast<const IMAGE*>(img), ice);
    };
    ctx.spawnSun = [this](int row, int col) {
        if (sunSpawner) sunSpawner(row, col);
    };

    for (int i = 0; i < g->row; ++i) {
        for (int j = 0; j < g->col; ++j) {
            plant* p = g->getPlant(i, j);
            if (!p) continue;
            // 植物需要知道自己在哪一格：射手据此判断右方是否有僵尸、子弹从哪里射出；
            // 向日葵据此决定阳光从哪一格落下。
            if (auto* sp = dynamic_cast<ShooterPlant*>(p)) sp->setGrid(i, j);
            else if (auto* sf = dynamic_cast<SunflowerPlant*>(p)) sf->setGrid(i, j);            p->onTick(deltaTime, ctx);
        }
    }
}

void battle_manager::updateZombies(float deltaTime) {
    // 先移除已死亡的僵尸，避免在下面的遍历里 erase 破坏迭代器
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
        [](const zombie& z) { return z.gethp() <= 0; }), zombies.end());

    for (auto& z : zombies) {
        const int row = z.getrow();
        bool eating = false;
        int eatCol = -1;

        // 僵尸与植物的接触判定。
        //
        // 僵尸移动是浮点型，按"取整后与植物所在格子比较"来判定：
        // 僵尸坐标 z.getx() 落到植物格子的整数列内才算接触，
        // 不再叠加中心偏移，让攻击距离再收近一些。
        constexpr float kCellW = 80.0f;
        constexpr float kFieldLeft = 170.0f;

        // 僵尸已经越过最左侧：直接判定失败并停止后续逻辑。
        // 原实现只在 x<10 时置结果，但循环体仍会继续执行，
        // 于是 eatTimer[row][负数] 写越界 —— 这也是调试断言崩溃的根因之一。
        if (z.getx() < kFieldLeft) {
            result = BattleResult::lose;
            continue;
        }

        if (row >= 0 && row < g->row) {
            const int col = static_cast<int>(std::floor((z.getx() - kFieldLeft) / kCellW));
            if (col >= 0 && col < g->col && g->getPlant(row, col)) {
                eatCol = col;
            }
        }

        if (eatCol >= 0) {
            eating = true;
            // 按格累计啃食时间；每结算一次就减去一个周期，而不是清零，
            // 否则同一格内多个僵尸会互相把计时重置，导致啃食速度被放大。
            eatTimer[row][eatCol] += deltaTime;
            while (eatTimer[row][eatCol] >= 1.0f) {
                g->damagePlant(row, eatCol, z.getattack());
                eatTimer[row][eatCol] -= 1.0f;
                if (!g->getPlant(row, eatCol)) {   // 植物已被吃掉
                    eating = false;
                    eatTimer[row][eatCol] = 0;
                    break;
                }
            }
        }

        if (!eating) z.move(deltaTime);

        putimagePNG(static_cast<int>(z.getx()) - 20, 90 + row * 100 - 70, &z.anim(eating));

        if (z.getx() < 10) {
            result = BattleResult::lose;   // 有僵尸进屋，本局失败
        }
    }
}

void battle_manager::updateBullets(float deltaTime) {
    // 子弹飞行速度。配合各射手的连发间隔，保证相邻豌豆相距约半个格子（40px）。
    constexpr float kBulletSpeed = 200.0f;
    constexpr float kCellW = 80.0f;
    constexpr float kFieldLeft = 170.0f;

    for (auto& b : bullets) {
        b.x += kBulletSpeed * deltaTime;

        if (b.x > 900) { b.active = false; continue; }   // 飞出右边界即失效

        // 穿过火焰树桩：点燃成火焰子弹（伤害提升，贴图替换）
        const int col = static_cast<int>(std::floor((b.x - kFieldLeft) / kCellW));
        if (col >= 0 && col < g->col) {
            plant* p = g->getPlant(b.row, col);
            auto* stump = dynamic_cast<TreeStumpPlant*>(p);
            if (stump && !b.fire) {
                b.fire = true;
                b.damage = static_cast<int>(b.damage * 1.5f);   // 火焰子弹伤害更高
                if (const IMAGE* fi = stump->fireBulletImg()) b.img = fi;
            }
        }

        putimagePNG(static_cast<int>(b.x), static_cast<int>(b.y - 40), b.img);

        for (auto& z : zombies) {
            if (z.getrow() != b.row || z.gethp() <= 0) continue;

            // 判断子弹是否在僵尸区域内
            if (b.x >= z.getx() && b.x <= z.getx() + 60) {
                z.takeDamage(b.damage);
                if (b.ice) z.applySlow(3.0f);   // 寒冰射手：命中减速 3 秒
                b.active = false;
                break;
            }
        }
    }

    // 统一移除失效子弹：原实现只标记 active=false 却留在容器里，
    // 导致越界和命中过的子弹永久堆积，每帧仍被重复处理。
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const bullet& b) { return !b.active; }), bullets.end());
}

void battle_manager::checkResult() {
    if (result != BattleResult::ongoing) return;
    if (spawnedCount >= totalToSpawn && zombies.empty()) {
        result = BattleResult::win;
    }
}

void battle_manager::update(float deltaTime) {
    trySpawnZombie(deltaTime);
    updatePlants(deltaTime);    // 植物行为（射击/产阳光）
    g->draw();                  // 先画植物
    updateBullets(deltaTime);   // 再画子弹，最后画僵尸，保证僵尸在最上层
    updateZombies(deltaTime);
    checkResult();
}
