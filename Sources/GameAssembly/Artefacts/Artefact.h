#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <random>
#include <memory>
#include "../Entities/Characters/Character.h"

enum class Quality {
    COMMON,
    RARE,
    EPIC,
    LEGENDARY,
    UNIQUE
};

class Artefact
{
protected:
    std::string name;
    std::string description;
    std::string droppedBy;
    Quality quality;
    int level = 1;

public:
    virtual ~Artefact() = default;
    Artefact();

    virtual void actingArtefact(Entity& target) = 0;
    virtual void onInflictedDamage(Entity& target) = 0;
    virtual void actingArtefactEveryTurns(Entity& target) = 0;

#pragma region Getters

    virtual std::string getName();
    virtual std::string getDescription();
    virtual std::string getDroppedBy();
    virtual int getLevel();
    virtual Quality getQuality();

#pragma endregion

#pragma region Setters

    void setLevel(int level);

#pragma endregion

};