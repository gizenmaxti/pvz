#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "zombie.h"
#include "bullet.h"
#include "grassland.h"
#include "battle_context.h"

enum class BattleResult { ongoing, win, lose };

class battle_manager {
public:
    battle_manager(int totals, int scount, float sTimer = 0, float sInterval = 4.0f)
        :totalToSpawn(totals), spawnedCount(scount), spawnTimer(sTimer), spawnInterval(sInterval) {

    }
    battle_manager()=default;
    void init(grassland* grass, int totalZombies);
    void update(float deltaTime);
    BattleResult getResult() const { return result; }

    // 向日葵产阳光时由植物回调触发；adventure_game 把它接到 sun_manager 上
    void setSunSpawner(std::function<void(int row, int col)> f) { sunSpawner = std::move(f); }

private:
    void trySpawnZombie(float deltaTime);
    void updateZombies(float deltaTime);
    void updatePlants(float deltaTime);
    void updateBullets(float deltaTime);
    void checkResult();

    grassland* g = nullptr;
    std::vector<zombie> zombies;
    std::vector<bullet> bullets;
    std::function<void(int row, int col)> sunSpawner;

    int totalToSpawn = 10;
    int spawnedCount = 0;
    float spawnTimer = 0;
    float spawnInterval = 4.0f;

    float eatTimer[5][9] = {};   // 每个格子独立的啃食计时（勿用函数级 static，会跨关卡残留）

    BattleResult result = BattleResult::ongoing;
};