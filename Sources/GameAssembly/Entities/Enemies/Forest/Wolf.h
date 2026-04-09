#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>

#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Wolf : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility(Character& target);
    void thirdAbility(int numberOfWolf);

    void fourthAbility(Character& target, int numberOfWolf);

    void startTurn() override;
    void endTurn() override;

    float powerAbilityOne = 0.9f;
    float powerAbilityTwo = 1.1f;

    int countWolves(const std::vector<std::shared_ptr<Entity>>& enemies);

public :
    Wolf(int floor);
    Wolf(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
