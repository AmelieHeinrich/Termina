#pragma once
#include <vector>
#include <type_traits>
#include "Enemy.h"

class EnemyManager {
public:

    EnemyManager();

    // Version template pour creer un ennemi
    template <typename T>
    void createEnemy(int floor) {
        static_assert(std::is_base_of<Enemy, T>::value, "T doit dériver de Enemy");
        enemies.push_back(std::make_shared<T>(floor));
    }

    void clearEnemies();
    void deleteEnemy(std::shared_ptr<Entity> enemy);
    std::vector<std::shared_ptr<Entity>>& getEnemies();

private:
    std::vector<std::shared_ptr<Entity>> enemies;
};
