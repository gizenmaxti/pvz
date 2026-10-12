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
    ctx.spawnSun = [this]() {
        if (sunSpawner) sunSpawner();
    };

    for (int i = 0; i < g->row; ++i) {
        for (int j = 0; j < g->col; ++j) {
            plant* p = g->getPlant(i, j);
            if (!p) continue;
            // 射手需要知道自己在哪一格，才能判断右方是否有僵尸、子弹从哪里射出
            if (auto* sp = dynamic_cast<ShooterPlant*>(p)) sp->setGrid(i, j);
            p->onTick(deltaTime, ctx);
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

        // 原实现只判断僵尸所在的整数格。僵尸从右侧靠近时，前端已经贴到植物了，
        // 它所在的格子却仍停在植物右边一格，于是出现"隔着一个格子就啃"的现象。
        // 正确判定：把僵尸整体当作一个矩形（前缘往前 30 像素、自身宽约 60 像素），
        // 找到它真正接触到的第一株植物。
        const float front = z.getx() - 30.0f;   // 僵尸前端（嘴）
        const float back = z.getx() + 60.0f;    // 僵尸尾部
        const int firstCol = static_cast<int>(std::floor((front - 170.0f) / 80.0f));
        const int lastCol = static_cast<int>(std::floor((back - 170.0f) / 80.0f));

        if (row >= 0 && row < g->row) {
            for (int c = firstCol; c <= lastCol; ++c) {
                if (c < 0 || c >= g->col) continue;
                if (g->getPlant(row, c)) { eatCol = c; break; }   // 取最靠右的被接触植物
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
            result = BattleResult::lose;
        }
    }
}

void battle_manager::updateBullets(float deltaTime) {
    for (auto& b : bullets) {
        b.x += 150.0f * deltaTime;

        if (b.x > 900) { b.active = false; continue; }   // 飞出右边界即失效

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
