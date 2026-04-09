#include "Diane.h"

Diane::Diane()
{
    name = "Diane";
    entityClass = EClass::TANK;
    description = "Diane, a fearless fighter, that doesn't hesitate to protect her fellow companions.";

    baseHealth = 100;
    finalHP = 1000;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 10.f;
    finalAD = 250;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 20;
    finalAP = 200;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 8;
    finalArmor = 50;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 6;
    finalPR = 30;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 100;
    currentSpeed = baseSpeed;
}

void Diane::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Diane uses \"Shield Charge\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD1 = 1;
}

void Diane::secondAbility(std::shared_ptr<Enemy>target)
{
    target->setIsTaunt(true);
    target->setTauntCD(3);
    LogManager::getInstance().addLog("Diane uses \"Taunt\". " + target->getName() + " is taunted.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD2 = 6;
}

void Diane::thirdAbility(std::shared_ptr<Character>target)
{
    shield += currentAttackPower;
    target->setShield(target->getShield() + currentAttackPower);
    LogManager::getInstance().addLog("Diane uses \"Shield Buff\". " + target->getName() + " and Diane get a Shield.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD3 = 4;
}

void Diane::fourthAbility(std::vector<std::shared_ptr<Entity>> &targets)
{
    for (auto character : targets) {
        if (character->getName() == getName()) {
            currentArmor = currentArmor * 1.3;
            LogManager::getInstance().addLog("The passive \"Bulk up\" of Diane give 30% Armor bonus to Diane, and 20% Armor bonus to the other characters.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
        else {
            character->setCurrentArmor(character->getCurrentArmor() * 1.2);
        }
    }

}

void Diane::startRun(std::vector<std::shared_ptr<Entity>> &targets)
{
    if (level >= 40){ fourthAbility(targets); }
}

void Diane::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 25) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Diane::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Diane::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Diane", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Shield Charge"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Taunt"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Shield Buff"))
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
                    firstAbility(selectedTargetE);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTargetE);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTargetC);
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

void Diane::Start() {}

void Diane::Update(float deltaTime) {}