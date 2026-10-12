#include "battle_manager.h"
#include "plant_registry.h"
#include "tool.h"
#include <cstdlib>
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
            attackCooldownTimer[i][j] = 0;
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
    for (auto it = zombies.begin(); it != zombies.end();) {
        if (it->gethp() <= 0) {
            it = zombies.erase(it);
            continue;
        }

        int col = static_cast<int>((it->getx() - 170) / 80);
        bool eating = false;

        if (col >= 0 && col < 9) {
            plant* p = g->getPlant(it->getrow(), col);
            if (p) {
                eating = true;
                // 每帧按秒结算伤害
                static float acc[5][9] = {}; // 简化：用静态数组累计吃植物的时间
                acc[it->getrow()][col] += deltaTime;
                if (acc[it->getrow()][col] >= 1.0f) {
                    g->damagePlant(it->getrow(), col, it->getattack());
                    acc[it->getrow()][col] = 0;
                }
            }
        }

        if (!eating) it->move(deltaTime);

        putimagePNG(static_cast<int>(it->getx()) - 20, 90 + it->getrow() * 100 - 70, &it->anim(eating));

        if (it->getx() < 10) {
            result = BattleResult::lose;
        }
        ++it;
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
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (!it->active) { ++it; continue; }

        it->x += 150.0f * deltaTime;

        if (it->x > 900) { it->active = false; ++it; continue; }

        putimagePNG(static_cast<int>(it->x), static_cast<int>(it->y - 40), it->img);

        for (auto& z : zombies) {
            if (z.getrow() != it->row || z.gethp() <= 0) continue;

            // 判断子弹是否在僵尸区域内
            if (it->x >= z.getx() && it->x <= z.getx() + 60) {
                z.takeDamage(it->damage);
                it->active = false;
                break;
            }
        }

        if (it->active) ++it;
        else it = bullets.erase(it);
    }
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