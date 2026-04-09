#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Ghost : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility(Character& target);

    void fourthAbility(Character& target);

    void startTurn() override;
    void endTurn() override;

public :
    Ghost(int floor);
    Ghost(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
