#include "Alex.h"

#include "../../../Artefacts/Common/SmokeBomb.h"

Alex::Alex()
{
    name = "Alex";
    entityClass = EClass::CLOSEDDPS;
    description = "Alex, the proud and generous white knight, that charges and slashes with his shield and big sword, defeating the evil.";

    baseHealth = 50;
    finalHP = 600;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 20.f;
    finalAD = 400;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 3;
    finalArmor = 30;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 2.f;
    finalPR = 20;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    currentSpeed = 90;
    baseSpeed = currentSpeed;

    isParring = false;
}

void Alex::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Alex uses \"Sword Slash\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD1 = 1;
}

void Alex::secondAbility()
{
    isParring = true;
    LogManager::getInstance().addLog("Alex uses \"Parade\". ", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD2 = 3;
}

void Alex::thirdAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage * 2 - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Alex uses \"Heavy Sword Slash\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));
    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD3 = 3;
}

void Alex::fourthAbility()
{
    float healthPercent = currentHealth / maxHealth * 100;
    if (healthPercent > 90)
    {
        currentAttackDamage = maxAttackDamage * 1;
        currentArmor = maxArmor * 1;
        currentPowerResist = maxPowerResist * 1;
        currentSpeed = 90;
    }
    else if (healthPercent > 80)
    {
        currentAttackDamage = maxAttackDamage * 1.1;
        currentArmor = maxArmor * 1.1;
        currentPowerResist = maxPowerResist * 1.1;
        currentSpeed = 88;
    }
    else if (healthPercent > 70)
    {
        currentAttackDamage = maxAttackDamage * 1.2;
        currentArmor = maxArmor * 1.2;
        currentPowerResist = maxPowerResist * 1.2;
        currentSpeed = 86;
    }
    else if (healthPercent > 60)
    {
        currentAttackDamage = maxAttackDamage * 1.3;
        currentArmor = maxArmor * 1.3;
        currentPowerResist = maxPowerResist * 1.3;
        currentSpeed = 84;
    }
    else if (healthPercent > 50)
    {
        currentAttackDamage = maxAttackDamage * 1.4;
        currentArmor = maxArmor * 1.4;
        currentPowerResist = maxPowerResist * 1.4;
        currentSpeed = 82;
    }
    else if (healthPercent > 40)
    {
        currentAttackDamage = maxAttackDamage * 1.5;
        currentArmor = maxArmor * 1.5;
        currentPowerResist = maxPowerResist * 1.5;
        currentSpeed = 80;
    }
    else if (healthPercent > 30)
    {
        currentAttackDamage = maxAttackDamage * 1.6;
        currentArmor = maxArmor * 1.6;
        currentPowerResist = maxPowerResist * 1.6;
        currentSpeed = 78;
    }
    else if (healthPercent > 20)
    {
        currentAttackDamage = maxAttackDamage * 1.7;
        currentArmor = maxArmor * 1.7;
        currentPowerResist = maxPowerResist * 1.7;
        currentSpeed = 76;
    }
    else if (healthPercent > 10)
    {
        currentAttackDamage = maxAttackDamage * 1.8;
        currentArmor = maxArmor * 1.8;
        currentPowerResist = maxPowerResist * 1.8;
        currentSpeed = 74;
    }
    else if (healthPercent > 0)
    {
        currentAttackDamage = maxAttackDamage * 2;
        currentArmor = maxArmor * 2;
        currentPowerResist = maxPowerResist * 2;
        currentSpeed = 70;
    }
}

void Alex::startTurn()
{
    if (isParring) { isParring = false; }

    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 5) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 15) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (level >= 30) fourthAbility();
}

void Alex::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Alex::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Alex", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Sword Slash"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Parade"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Heavy Sword Slash"))
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
            ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f + viewport->Size.y * 1.0f / 3.0f));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y - viewport->Size.y / 8.0f - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y * 1.0f / 3.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Choose enemy target", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            for (int i = 0; i < enemies.size(); i++)
            {
                std::string label = enemies[i]->getName() + "##" + std::to_string(i);

                if (ImGui::Button(label.c_str())) {
                    selectedTarget = std::static_pointer_cast<Enemy>(enemies[i]);
                    currentState = PlayerState::ACTING;
                }
            }

            if (ImGui::Button("Return")) {
                currentState = PlayerState::CHOOSINGABILITY;
            }

            ImGui::End();
            ImGui::PopStyleColor();
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
                    secondAbility();
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTarget);
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

void Alex::Start() {}

void Alex::Update(float deltaTime) {}

bool Alex::getIsParring() { return isParring; }