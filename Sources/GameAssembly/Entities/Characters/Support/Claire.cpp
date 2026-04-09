#include "Claire.h"

#include <random>

Claire::Claire()
{
    name = "Claire";
    entityClass = EClass::SUPPORT;
    description = "Claire; Her deep learning of magic is now put to action and make her a big support for her team. She doesn't bright by her bodily acts but by her intelligence.";

    baseHealth = 50;
    finalHP = 400;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 3;
    finalAD = 100;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 10;
    finalAP = 20;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.2;
    finalArmor = 10;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.4;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 80;
    currentSpeed = baseSpeed;
}

void Claire::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> chance(1, 100);
    std::uniform_int_distribution<int> dist(1, 5);

    if (chance(rng) <= 15)
    {
        float choice = dist(rng);

        if (choice == 1) {
            target->setCurrentAttackDamage(target->getCurrentAttackDamage() - target->getCurrentAttackDamage() * 0.05);
            LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes Attack Damage malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
        else if (choice == 2) {
            target->setCurrentAttackPower(target->getCurrentAttackPower() - target->getCurrentAttackPower() * 0.05);
            LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes Attack Power malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
        else if (choice == 3) {
            target->setCurrentArmor(target->getCurrentArmor() - target->getCurrentArmor() * 0.05);
            LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes Armor malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
        else if (choice == 4) {
            target->setCurrentPowerResist(target->getCurrentPowerResist() - target->getCurrentPowerResist() * 0.05);
            LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes Power Resist malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
        else if (choice == 5) {
            target->setCurrentSpeed(target->getCurrentSpeed() + currentAttackPower);
            LogManager::getInstance().addLog("Claire uses \"Wand Hit\". " + target->getName() + " takes Speed malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
        }
    }

    CD1 = 1;
}

void Claire::secondAbility(std::shared_ptr<Character>target)
{
    target->setCurrentArmor(target->getCurrentArmor() * 1.05);
    target->setCurrentPowerResist(target->getCurrentPowerResist() * 1.05);
    LogManager::getInstance().addLog("Claire uses \"Resist Buff\". " + target->getName() + " takes Armor and Power Resist bonus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD2 = 4;
}

void Claire::thirdAbility(std::shared_ptr<Enemy>target)
{
    target->setCurrentSpeed(target->getCurrentSpeed() + currentAttackPower);
    LogManager::getInstance().addLog("Claire uses \"Slow Debuff\". " + target->getName() + " takes Speed malus.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD3 = 6;
}

void Claire::fourthAbility(std::shared_ptr<Character>target)
{
    target->setCurrentAttackPower(target->getCurrentAttackPower() * 1.1);
    target->setCurrentAttackDamage(target->getCurrentAttackDamage() * 1.1);
    target->setCurrentArmor(target->getCurrentArmor() * 1.1);
    target->setCurrentPowerResist(target->getCurrentPowerResist() * 1.1);
    target->setCurrentSpeed(target->getCurrentSpeed() - currentAttackPower);

    LogManager::getInstance().addLog("Claire uses \"Mega Buff\". " + target->getName() + " takes a bonus in all stats.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD4 = 11;
}

void Claire::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 16) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 25) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Claire::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Claire::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Claire", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Wand Hit"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Defense Buff"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Slow Debuff"))
            {
                abilitySelected = 3;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Mega Buff"))
            {
                abilitySelected = 4;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }

        case PlayerState::CHOOSINGTARGET :
        {
            if (abilitySelected == 1 or abilitySelected == 3)
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
                    secondAbility(selectedTargetC);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTargetE);
                    break;
                }
                case 4 : {
                    fourthAbility(selectedTargetC);
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

void Claire::Start() {}

void Claire::Update(float deltaTime) {}