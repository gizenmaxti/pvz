#pragma once
#include<unordered_map>
#include<functional>
#include<memory>
#include"plantinfo.h"

class plant;   // 前向声明即可：此处只用到 unique_ptr<plant> 作为返回值，
               // 不需要完整定义，避免与 plant_base.h 互相包含

class plant_registry {
public:
    static plant_registry& instance() {
        static plant_registry instance;
        return instance;
    }

    void putconfig(Planttype t, plantinfo p) {
        plant_infos.emplace(t, p);
    }

    const plantinfo& get_plant_info(Planttype type) const {
        return plant_infos.at(type);
    }

    // 注册某类植物的构造函数，使 grassland 能在运行时创建正确的子类。
    // 新增植物只需"注册配置 + 注册工厂"，不必修改任何 if/switch。
    static void setCreator(Planttype t, std::function<std::unique_ptr<plant>()> creator) {
        creators()[t] = std::move(creator);
    }

    static std::unique_ptr<plant> create(Planttype t);

    void load();

private:
    static std::unordered_map<Planttype, std::function<std::unique_ptr<plant>()>>& creators() {
        static std::unordered_map<Planttype, std::function<std::unique_ptr<plant>()>> m;
        return m;
    }

    std::unordered_map<Planttype, plantinfo> plant_infos;
};
