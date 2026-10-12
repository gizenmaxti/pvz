#pragma once
#include <functional>
#include <vector>

class zombie;

// 植物行为所需的外部环境。
//
// 这里刻意不让植物直接持有 battle_manager：那样会形成
// plant -> battle_manager -> grassland -> plant 的循环依赖。
// 改由 battle_manager 每帧把只读的僵尸列表和两个回调注入进来。
struct BattleContext {
    std::vector<zombie>* zombies = nullptr;
    std::function<void(float x, float y, int row, int damage, const void* img, bool ice)> spawnBullet;
    // 产出阳光：带上产出的植物所在格，阳光会从该位置落下
    std::function<void(int row, int col)> spawnSun;
};
