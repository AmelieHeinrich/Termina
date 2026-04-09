#pragma once
#include "../Character.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Marcus : public Character, public TerminaScript::ScriptableComponent
{
    std::shared_ptr<Character> selectedTarget = nullptr;

    void startTurn() override;
    void endTurn() override;

    void firstAbility(std::shared_ptr<Character>target);
    void secondAbility(std::vector<std::shared_ptr<Entity>>& targets);
    void thirdAbility(std::shared_ptr<Character>target);
    void fourthAbility(std::shared_ptr<Character>target);

public :
    Marcus();
    Marcus(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;
};
