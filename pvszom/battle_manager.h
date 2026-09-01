#pragma once
#include <vector>
#include "zombie.h"
#include "bullet.h"
#include "grassland.h"

enum class BattleResult { ongoing, win, lose };

class battle_manager {
public:
    void init(grassland* grass, int totalZombies);
    void update(float deltaTime);
    BattleResult getResult() const { return result; }

private:
    void trySpawnZombie(float deltaTime);
    void updateZombies(float deltaTime);
    void updatePlantAttacks(float deltaTime);
    void updateBullets(float deltaTime);
    void checkResult();

    grassland* g = nullptr;
    std::vector<zombie> zombies;
    std::vector<bullet> bullets;

    int totalToSpawn = 10;
    int spawnedCount = 0;
    float spawnTimer = 0;
    float spawnInterval = 4.0f;

    float attackCooldownTimer[5][9] = {}; // 每个格子独立的攻击冷却计时

    BattleResult result = BattleResult::ongoing;
};