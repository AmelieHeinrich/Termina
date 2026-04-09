#include "Marcus.h"

#include "../../../Artefacts/Artefact.h"

Marcus::Marcus()
{
    name = "Marcus";
    entityClass = EClass::SUPPORT;
    description = "Marcus, born among the priests of the local church, he became himself a monk capable of the most incredible spells. Expelled from his home because of the fear of those who taught him, he now travels to where his destiny calls him according to him.";

    baseHealth = 40;
    finalHP = 300;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 10;
    finalAP = 300;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 3;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 5;
    finalPR = 15;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 85;
    currentSpeed = baseSpeed;
}

void Marcus::firstAbility(std::shared_ptr<Character>target)
{
    float HPHealed = currentAttackPower / 2;

    target->setCurrentHealth(target->getCurrentHealth() + HPHealed);
    if (target->getCurrentHealth() > target->getMaxHealth()) { target->setCurrentHealth(target->getMaxHealth()); }
    LogManager::getInstance().addLog("Marcus uses \"Heal\". " + target->getName() + " is healed.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD1 = 1;
}

void Marcus::secondAbility(std::vector<std::shared_ptr<Entity>>& characters)
{
    float HPHealed = currentAttackPower / 4;

    for (auto& target : characters) {
        target->setCurrentHealth(target->getCurrentHealth() + HPHealed);
        if (target->getCurrentHealth() > target->getMaxHealth()) { target->setCurrentHealth(target->getMaxHealth()); }
        LogManager::getInstance().addLog("Marcus uses \"Multi-Heal\". " + target->getName() + " is healed.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
    }

    CD2 = 4;
}

void Marcus::thirdAbility(std::shared_ptr<Character>target)
{
    target->setIsBurnt(false);
    target->setBurnCD(0);
    target->setIsPoisoned(false);
    target->setPoisonCD(0);
    target->setIsStun(false);
    target->setCurrentAttackPower(target->getMaxAttackPower());
    target->setCurrentAttackDamage(target->getMaxAttackDamage());
    target->setCurrentArmor(target->getMaxArmor());
    target->setCurrentPowerResist(target->getMaxPowerResist());
    LogManager::getInstance().addLog("Marcus uses \"Cleans\". " + target->getName() + "'s debuffs are suppressed.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD3 = 3;
}

void Marcus::fourthAbility(std::shared_ptr<Character>target)
{
    target->setCurrentHealth(target->getMaxHealth() / 2);
    LogManager::getInstance().addLog("Marcus uses \"Resurrection\". " + target->getName() + " is revived.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD4 = 11;
}

void Marcus::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 35) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Marcus::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Marcus::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Marcus", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Heal"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Multi Heal"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Cleans"))
            {
                abilitySelected = 3;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Resurrection"))
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
            if (abilitySelected != 4)
            {
                ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f + viewport->Size.y * 1.0f / 3.0f));
                ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y - viewport->Size.y / 8.0f - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y * 1.0f / 3.0f));
                ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
                ImGui::Begin("Choose Ally target", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
                for (int i = 0; i < characters.size(); i++)
                {
                    std::string label = characters[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTarget = std::static_pointer_cast<Character>(characters[i]);
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
                    if (characters[i]->getCurrentHealth() <= 0)
                    {
                        std::string label = characters[i]->getName() + "##" + std::to_string(i);

                        if (ImGui::Button(label.c_str())) {
                            selectedTarget = std::static_pointer_cast<Character>(characters[i]);
                            currentState = PlayerState::ACTING;
                        }
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
                    firstAbility(selectedTarget);
                    break;
                }
                case 2 : {
                    secondAbility(characters);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTarget);
                    break;
                }
                case 4 : {
                    fourthAbility(selectedTarget);
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

void Marcus::Start() {}

void Marcus::Update(float deltaTime) {}