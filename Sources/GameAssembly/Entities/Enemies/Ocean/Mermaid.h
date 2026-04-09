#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Mermaid : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility(Character& target, std::vector<std::shared_ptr<Entity>> enemies);
    void thirdAbility(Enemy& target);

    void fourthAbility(std::vector<std::shared_ptr<Entity>> enemies);

    void startTurn() override;
    void endTurn() override;

public :
    Mermaid(int floor);
    Mermaid(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
