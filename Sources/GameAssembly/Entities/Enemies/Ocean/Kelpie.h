#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Kelpie : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility(Character& target1, Character& target2, Character& target3);
    void thirdAbility();

    void fourthAbility();

    void startTurn() override;
    void endTurn() override;

    void manageKelpieEffects();

public :
    Kelpie(int floor);
    Kelpie(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
