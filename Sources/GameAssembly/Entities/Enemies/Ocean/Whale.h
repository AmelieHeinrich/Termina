#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Whale : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(const std::vector<Character*>& targets);
    void secondAbility(const std::vector<Enemy*>& targets);
    void thirdAbility(Enemy& target);

    void fourthAbility(std::vector<std::shared_ptr<Entity>> enemies);

    void startTurn() override;
    void endTurn() override;

public :
    Whale(int floor);
    Whale(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
