#include "battle_manager.h"
#include "plant_registry.h"
#include "tool.h"
#include <cstdlib>
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
        for (int j = 0; j < 9; ++j) {
            attackCooldownTimer[i][j] = 0;
            eatTimer[i][j] = 0;
        }
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

void battle_manager::updateZombies(float deltaTime) {
    // 先移除已死亡的僵尸，避免在下面的遍历里 erase 破坏迭代器
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
        [](const zombie& z) { return z.gethp() <= 0; }), zombies.end());

    for (auto& z : zombies) {
        const int row = z.getrow();
        const int col = static_cast<int>((z.getx() - 170) / 80);
        bool eating = false;

        if (col >= 0 && col < g->col && row >= 0 && row < g->row) {
            if (g->getPlant(row, col)) {
                eating = true;
                // 按格累计啃食时间；每结算一次就减去一个周期，而不是清零，
                // 否则同一格内多个僵尸会互相把计时重置，导致啃食速度被放大。
                eatTimer[row][col] += deltaTime;
                while (eatTimer[row][col] >= 1.0f) {
                    g->damagePlant(row, col, z.getattack());
                    eatTimer[row][col] -= 1.0f;
                    if (!g->getPlant(row, col)) {   // 植物已死，停止啃食
                        eating = false;
                        eatTimer[row][col] = 0;
                        break;
                    }
                }
            }
            else {
                eatTimer[row][col] = 0;   // 该格没有植物，计时归零
            }
        }

        if (!eating) z.move(deltaTime);

        putimagePNG(static_cast<int>(z.getx()) - 20, 90 + row * 100 - 70, &z.anim(eating));

        if (z.getx() < 10) {
            result = BattleResult::lose;
        }
    }
}

void battle_manager::updatePlantAttacks(float deltaTime) {
    for (int i = 0; i < g->row; ++i) {
        for (int j = 0; j < g->col; ++j) {
            plant* p = g->getPlant(i, j);
            if (!p || !p->canAttack()) continue;

            attackCooldownTimer[i][j] += deltaTime;
            if (attackCooldownTimer[i][j] < 1.5f) continue;

            bool zombieAhead = false;
            for (auto& z : zombies) {
                if (z.getrow() == i && z.getx() > 170 + j * 80) {
                    zombieAhead = true;
                    break;
                }
            }
            if (zombieAhead) {
                attackCooldownTimer[i][j] = 0;
                bullets.emplace_back(170 + j * 80 + 60, 90 + i * 100 + 40, i, p->getDamage(), &p->getBulletImg());
            }
        }
    }
}

//void battle_manager::updateBullets(float deltaTime) {
//    for (auto it = bullets.begin(); it != bullets.end();) {
//        if (it->active) {
//            putimagePNG(static_cast<int>(it->x), static_cast<int>(it->y - 40), it->img);
//        }
//
//        it->x += 150.0f * deltaTime; // 子弹飞行速度：像素/秒
//
//        for (auto& z : zombies) {
//            if (z.getrow() == it->row && it->x > z.getx() && it->x <= z.getx() + 60 && z.gethp() > 0) {
//                z.takeDamage(it->damage);
//                it->active = false;
//                break;
//            }
//        }
//
//        if (it->x > 900) it->active = false;
//
//        ++it;
//    }
//}
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
    updatePlantAttacks(deltaTime);
    updateBullets(deltaTime);
    updateZombies(deltaTime);
    checkResult();
}