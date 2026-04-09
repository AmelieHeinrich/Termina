#include "Brutus.h"

Brutus::Brutus()
{
    name = "Brutus";
    entityClass = EClass::RANGEDDPS;
    description = "Brutus, the solitary archer, he is used to stay alone but knows how to be useful in a group in the battlefield. He often invents new arrows to content his best friend : his bow.";

    baseHealth = 40;
    finalHP = 500;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 15;
    finalAD = 300;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 3;
    finalAP = 120;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 2.f;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 2.f;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 80;
    currentSpeed = baseSpeed;
}

void Brutus::firstAbility(std::shared_ptr<Enemy>target)
{
    for (int i = 0; i < 3; i++)
    {
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
        LogManager::getInstance().addLog("Brutus uses \"Triple Shoot\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

        if (artefact) {
            artefact->onInflictedDamage(*this);
        }
    }

    CD1 = 1;
}

void Brutus::secondAbility(std::shared_ptr<Enemy>target)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> arrows(5, 10);

    int arrowToShoot = arrows(rng);

    for (int i = 0; i < arrowToShoot; i++)
    {
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
        LogManager::getInstance().addLog("Brutus uses \"Arrow Storm\". " + target->getName() + " takes damages (x" + std::to_string(arrowToShoot) + ").", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

        if (artefact) {
            artefact->onInflictedDamage(*this);
        }
    }

    CD2 = 5;
}

void Brutus::thirdAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() * 0.2 / 100 );
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Brutus uses \"Piercing Arrow\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD3 = 6;
}

void Brutus::fourthAbility(std::shared_ptr<Enemy>target)
{
    float dmgAPDealt = currentAttackPower * 4 - currentAttackPower * (target->getCurrentPowerResist() / 100);
    float dmgADDealt = currentAttackDamage * 4 - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - (dmgADDealt + dmgAPDealt) / 2);
    LogManager::getInstance().addLog("Brutus uses \"Explosive Arrow\". " + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD4 = 11;
}

void Brutus::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 5) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 18) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 37) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Brutus::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Brutus::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            ImGui::Begin("Choose Ability - Brutus", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Triple Shoot"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Arrow's Storm"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Piercing Arrow"))
            {
                abilitySelected = 3;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Explosive Arrow"))
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
                case 4 :
                {
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

void Brutus::Start() {}

void Brutus::Update(float deltaTime) {}