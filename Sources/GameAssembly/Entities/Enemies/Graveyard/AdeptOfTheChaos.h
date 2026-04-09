#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class AdeptOfTheChaos : public Enemy, public TerminaScript::ScriptableComponent
{
    void firstAbility(Character& target);
    void secondAbility(Character& target);
    void thirdAbility();

    void fourthAbility(const std::vector<Character*>& targets);

    void startTurn() override;
    void endTurn() override;

    float powerAbilityOne = 0.9;
    float powerAbilityTwo = 1.1;
    float powerAbilityFour = 1.5;

public :
    AdeptOfTheChaos(int floor);
    AdeptOfTheChaos(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    std::shared_ptr<Artefact> createDrop() override;
};
