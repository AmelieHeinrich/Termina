#include "Penelope.h"

Penelope::Penelope()
{
    name = "Penelope";
    entityClass = EClass::CLOSEDDPS;
    description = "Penelope, hidden in the shadows, secretly eliminates all that appears in her way with her poisonous blades.";

    baseHealth = 45;
    finalHP = 300;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 18;
    finalAD = 450;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 1.f;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 1.f;
    finalPR = 20;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 62.5;
    currentSpeed = baseSpeed;

    fourthAbilityActive = false;
}

void Penelope::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Penelope uses \"Cut\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD1 = 1;
}

void Penelope::secondAbility(std::shared_ptr<Enemy>target)
{
    target->setIsPoisoned(true);
    target->setPoisonCD(5);
    LogManager::getInstance().addLog("Penelope uses \"Poison\". " + target->getName() + " is poisoned.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD2 = 3;
}

void Penelope::thirdAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage * 2 - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    currentHealth += dmgDealt * (80 / 100);
    LogManager::getInstance().addLog("Penelope uses \"Vampiric Cut\". " + target->getName() + " takes damages and a part of the damages inflicted are used to heal Penelope.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD3 = 4;
}

void Penelope::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (level >= 45) fourthAbilityActive = true;
}

void Penelope::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Penelope::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Penelope", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Cut"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Poison"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Vampiric Cut"))
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
                    secondAbility(selectedTarget);
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

void Penelope::Start() {}

void Penelope::Update(float deltaTime) {}