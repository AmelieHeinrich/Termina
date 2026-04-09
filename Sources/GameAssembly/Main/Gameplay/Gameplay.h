#pragma once

#include <vector>
#include <memory>
#include <random>

#include "../../../ThirdParty/ImGui/imgui.h"
#include "../../../ThirdParty/ImGui/ImGuizmo.h"
#include "../../../ThirdParty/ImGui/imgui_internal.h"

#include "../../Entities/Enemies/EnemyManager.h"
#include "../../Entities/Characters/Character.h"
#include "../Inventory.h"
#include "../PlayerXP.h"

enum class EBiome {
    FOREST,
    OCEAN,
    GRAVEYARD
};

enum class EGameRunState
{
    STARTRUN,
    CHECKUPGRADE,
    STARTFIGHT,
    UPDATEFIGHT,
    ENDFIGHT,
    ENDRUN
};

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::unique_ptr<PlayerXP> playerXP;
    std::vector<std::shared_ptr<Entity>> activeCharacters;
    std::vector<std::shared_ptr<Entity>> speedManagerVec;
    std::vector<std::shared_ptr<Entity>> aliveCharaVec;
    std::shared_ptr<Inventory> inventory;

    EGameRunState runState;
    EBiome currentBiome;


    bool spawnBoss = false;
    std::random_device rd;

    int currentLevel = 1;
    int biomeCount = 0;

    bool runEnded = false;

    int currentEntityIndex = 0;

    bool enemySpawned = false;
    bool destroyCharacter = false;
    bool destroyEnemy = false;


public:

    Gameplay();
    void startRun();
    void endRun();

    void startFight();
    void endFight();

    void gameloop();
    void updateFight();

    bool hasSameType(const Entity& entity) const;
    void addToTeam(const std::shared_ptr<Entity>& entity);
    void removeFromTeam(const std::shared_ptr<Entity>& entity);

    void drawImGui();

    bool teamIsComplete();
    bool isInTeam(const std::shared_ptr<Entity>& entity);



    void setRunState(EGameRunState newState);
    void setRunEnded(bool gameEnded);

    bool getRunEnded() const;

    bool getEnemySpawned() const { return enemySpawned; }
    bool setEnemySpawned(bool newBool);

    bool getDestroyCharacter() const { return destroyCharacter; }
    bool setDestroyCharacter(bool newBool);

    bool getDestroyEnemy() const { return destroyCharacter; }
    bool setDestroyEnemy(bool newBool);

    std::vector<std::shared_ptr<Entity> > getActiveCharacters() { return activeCharacters;};
    std::vector<std::shared_ptr<Entity> > getEnemyVector() {return enemyManager->getEnemies();}
};

