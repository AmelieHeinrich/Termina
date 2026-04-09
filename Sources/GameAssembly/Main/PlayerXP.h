#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <map>
#include "../Entities/Characters/Character.h"

enum class EUpgradeState {
    CHECKINGXP,
    GENERATEUPGRADE,
    CHOOSINGUPGRADE,
    SELECTTARGET,
    SELECTCLASS
};

enum class EBonusType {
    HEALALL,
    HEALSINGLE,
    AP,
    AD,
    ARMOR,
    MAGICRESIST,
    CLASSSTATS,
    UPGRADECHANCE
};

struct Bonus {
    EBonusType type;
    EClass bonusClass;
    std::shared_ptr<Entity> character;
    float value;
    int rarity;
};

struct BonusValues {
    float healAll;
    float healSingle;
    float ap;
    float ad;
    float armor;
    float mr;
    float classStats;
    float upgradeChance;
};

class PlayerXP {

    float currentXP;
    float XPNeededForLvl2;
    float XPNeeded;
    float finalXPNeeded;

    bool choosing;

    ImVec4 color;

    EUpgradeState upgradeState;

    std::random_device rd;
    int range = 100;

    std::vector<Bonus> bonusChoices;

    std::vector<std::unique_ptr<Bonus>> bonusesToApply;

    std::map<int, BonusValues> rarityTable = {
        {1, {10, 50, 2, 2, 2, 2, 2, 5}},    // Common
        {2, {15, 65, 5, 5, 5, 5, 4, 10}},   // Rare
        {3, {20, 75, 7.5, 7.5, 10, 10, 8, 15}}, // Epic
        {4, {30, 100, 10, 10, 15, 15, 10, 20}}  // Legendary
    };

    Bonus generateBonus(int rarity);
    std::string getBonusText(const Bonus& bonus);

    std::string getRarityString(int rarity);

public:
    PlayerXP();

    void startRun();

    bool upgradeSystem(int level, std::vector<std::shared_ptr<Entity>> characters);
    bool levelUp(int level);
    void applyBonuses(std::vector<std::shared_ptr<Entity>> characters);

    bool getChoosing() const;
    void addCurrentXP(int xpToAdd);
};

