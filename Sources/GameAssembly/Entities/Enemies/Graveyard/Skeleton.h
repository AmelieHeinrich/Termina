#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Skeleton : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility();
    void thirdAbility();

    void fourthAbility();

    void startTurn() override;
    void endTurn() override;

public :
    Skeleton(int floor);
    Skeleton(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
