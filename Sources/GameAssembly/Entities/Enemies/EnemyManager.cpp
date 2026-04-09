//
// Created by lmarcucci on 18/03/2026.
//

#include "EnemyManager.h"
#include <algorithm>
#include <memory>

EnemyManager::EnemyManager() {}

void EnemyManager::clearEnemies() { enemies.clear(); }

void EnemyManager::deleteEnemy(std::shared_ptr<Entity> enemy) {
    std::erase(enemies, enemy);
}

std::vector<std::shared_ptr<Entity>>& EnemyManager::getEnemies() { return enemies; }