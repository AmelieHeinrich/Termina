#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class RunicDeer : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    RunicDeer(int floor);
    RunicDeer(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts();

    void firstAbility(Character& target);
    void secondAbility(Character& target, Enemy& enemyTarget);
    void thirdAbility();

    void fourthAbility(const std::vector<Character*>& targets);

    std::shared_ptr<Artefact> createDrop() override;

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;
};
