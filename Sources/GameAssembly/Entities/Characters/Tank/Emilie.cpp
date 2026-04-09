#include "Emilie.h"

#include <algorithm>
#include <memory>

Emilie::Emilie()
{
    name = "Emilie";
    entityClass = EClass::TANK;
    description = "Emilie has worked her whole life in a forge, it gave her an unbreakable skin and preeminent muscles that allows her to be a great defender for her team.";

    baseHealth = 90;
    finalHP = 900;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 8;
    finalAD = 300;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 2;
    finalArmor = 20;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 5;
    finalPR = 50;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 95;
    currentSpeed = baseSpeed;
}

void Emilie::firstAbility(std::vector<std::shared_ptr<Entity>> enemies)
{
    for (auto& target : enemies) {
        if (target != nullptr){
            float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
            target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
            LogManager::getInstance().addLog("Emilie uses \"Earthquake\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

            if (artefact) {
                artefact->onInflictedDamage(*this);
            }
        }
    }

    CD1 = 1;
}

void Emilie::secondAbility(std::shared_ptr<Character> target)
{
    target->setCurrentPowerResist(target->getCurrentPowerResist() + maxPowerResist / 2);
    LogManager::getInstance().addLog("Emilie uses \"Share\". " + target->getName() + " takes Power Resist bonus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD2 = 5;
}

void Emilie::thirdAbility(std::vector<std::shared_ptr<Entity>> enemies)
{
    for (auto& target : enemies) {
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 4);
        target->setIsStun(true);
        LogManager::getInstance().addLog("Emilie uses \"Punch'em all\". " + target->getName() + " takes damages and is stunned.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

        if (artefact) {
            artefact->onInflictedDamage(*this);
        }
    }

    CD3 = 5;
}

bool Emilie::canBeAttacked(std::shared_ptr<Enemy> target)
{
    if (std::find(currentEnemies.begin(), currentEnemies.end(), target) != currentEnemies.end() and level >= 45)
    {
        currentEnemies.erase(std::find(currentEnemies.begin(), currentEnemies.end(), target));
        return false;
    }
    return true;
}

void Emilie::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 6) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Emilie::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Emilie::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (currentState) {
        case PlayerState::STARTTURN : {
            startTurn();

            if (artefact && !artefactAlreadyUsed) {
                artefact->actingArtefact(*this);
                artefactAlreadyUsed = true;
            }

            currentState = PlayerState::CHOOSINGABILITY;
            break;
        }

        case PlayerState::CHOOSINGABILITY : {
            ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f + viewport->Size.y * 1.0f / 3.0f));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y - viewport->Size.y / 8.0f - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y * 1.0f / 3.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Choose Ability - Emilie", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Earthquake"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Share"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Punch'em all"))
            {
                abilitySelected = 3;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }

        case PlayerState::CHOOSINGTARGET :
        {
            if (abilitySelected == 1 or abilitySelected == 2)
            {
                ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f + viewport->Size.y * 1.0f / 3.0f));
                ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y - viewport->Size.y / 8.0f - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y * 1.0f / 3.0f));
                ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
                ImGui::Begin("Choose enemy target", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
                for (int i = 0; i < enemies.size(); i++)
                {
                    std::string label = enemies[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTargetE = std::static_pointer_cast<Enemy>(enemies[i]);
                        currentState = PlayerState::ACTING;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::CHOOSINGABILITY;
                }

                ImGui::End();
                ImGui::PopStyleColor();
            }
            else
            {
                ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f + viewport->Size.y * 1.0f / 3.0f));
                ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y - viewport->Size.y / 8.0f - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y * 1.0f / 3.0f));
                ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
                ImGui::Begin("Choose ally target", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
                for (int i = 0; i < characters.size(); i++)
                {
                    std::string label = characters[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTargetC = std::static_pointer_cast<Character>(characters[i]);
                        currentState = PlayerState::ACTING;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::CHOOSINGABILITY;
                }

                ImGui::End();
                ImGui::PopStyleColor();
            }
            break;
        }

        case PlayerState::ACTING :
        {
            switch (abilitySelected) {
                case 1 : {
                    firstAbility(enemies);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTargetC);
                    break;
                }
                case 3 : {
                    thirdAbility(enemies);
                    break;
                }
                default : {
                    currentState = PlayerState::CHOOSINGABILITY;
                }

            }
            currentState = PlayerState::ENDTURN;
            break;
        }

        case PlayerState::ENDTURN : {
            endTurn();
            if (artefact) {
                artefact->actingArtefactEveryTurns(*this);
            }

            currentState = PlayerState::STARTTURN;
            return true;
        }
    }
    return false;
}

void Emilie::startFight(std::vector<std::shared_ptr<Entity>>& enemies) {
    for (auto& enemy : enemies) {
        currentEnemies.push_back(std::dynamic_pointer_cast<Enemy>(enemy));
    }
}

void Emilie::endFight() {
    currentEnemies.clear();
}

void Emilie::Start() {}

void Emilie::Update(float deltaTime) {}