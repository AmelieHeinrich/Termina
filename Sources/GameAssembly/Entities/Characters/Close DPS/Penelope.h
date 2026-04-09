#pragma once

#include "../Character.h"
#include "../../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Penelope : public Character, public TerminaScript::ScriptableComponent
{
    bool fourthAbilityActive;
    std::shared_ptr<Enemy> selectedTarget = nullptr;

    void startTurn() override;
    void endTurn() override;

    void firstAbility(std::shared_ptr<Enemy>target);
    void secondAbility(std::shared_ptr<Enemy>target);
    void thirdAbility(std::shared_ptr<Enemy>target);

public :
    Penelope();
    Penelope(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;
};