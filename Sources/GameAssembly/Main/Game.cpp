#include "Game.h"

#include <iostream>
#include <ostream>

#include "../Termina/Renderer/Components/CameraComponent.hpp"
#include "../Termina/Renderer/Components/MeshComponent.hpp"
#include "../Termina/Scripting/API/ScriptableComponent.hpp"
#include "../Termina/World/Actor.hpp"

#include "../Entities/Characters/Close DPS/Alex.h"
#include "../Entities/Characters/Close DPS/Penelope.h"
#include "../Entities/Characters/Tank/Diane.h"
#include "../Entities/Characters/Tank/Emilie.h"
#include "../Entities/Characters/Support/Marcus.h"
#include "../Entities/Characters/Support/Claire.h"
#include "../Entities/Characters/Range DPS/Brutus.h"
#include "../Entities/Characters/Range DPS/Edward.h"


void Game::Start()
{
    if (!gameplay) {
        gameplay = std::make_unique<Gameplay>();
    }
    gameState = EGameState::Title;

#pragma region FillAllCharacters
    allCharacters.emplace_back(std::make_shared<Diane>());
    allCharacters.emplace_back(std::make_shared<Emilie>());
    allCharacters.emplace_back(std::make_shared<Claire>());
    allCharacters.emplace_back(std::make_shared<Marcus>());
    allCharacters.emplace_back(std::make_shared<Brutus>());
    allCharacters.emplace_back(std::make_shared<Edward>());
    allCharacters.emplace_back(std::make_shared<Alex>());
    allCharacters.emplace_back(std::make_shared<Penelope>());
#pragma endregion

    /////// Link Names -> Prefab
#pragma region MappingPrefab-Names
    p_Diane = TerminaScript::Prefab("Assets/Prefabs/Diane.trp");
    p_Emilie = TerminaScript::Prefab("Assets/Prefabs/Emilie.trp");
    p_Claire = TerminaScript::Prefab("Assets/Prefabs/Claire.trp");
    p_Marcus = TerminaScript::Prefab("Assets/Prefabs/Marcus.trp");
    p_Brutus = TerminaScript::Prefab("Assets/Prefabs/Brutus.trp");
    p_Edward = TerminaScript::Prefab("Assets/Prefabs/Edward.trp");
    p_Alex = TerminaScript::Prefab("Assets/Prefabs/Alex.trp");
    p_Penelope = TerminaScript::Prefab("Assets/Prefabs/Penelope.trp");

    p_Rat = TerminaScript::Prefab("Assets/Prefabs/Rat.trp");
    p_Wolf = TerminaScript::Prefab("Assets/Prefabs/Wolf.trp");
    p_Hawk = TerminaScript::Prefab("Assets/Prefabs/Hawk.trp");
    p_Bear = TerminaScript::Prefab("Assets/Prefabs/Bear.trp");

    p_Ghost = TerminaScript::Prefab("Assets/Prefabs/Ghost.trp");
    p_Gargoyle = TerminaScript::Prefab("Assets/Prefabs/Gargoyle.trp");
    p_Skeleton = TerminaScript::Prefab("Assets/Prefabs/Skeleton.trp");
    p_AdeptOfTheChaos = TerminaScript::Prefab("Assets/Prefabs/AdeptOfTheChaos.trp");
    p_DarkKnight = TerminaScript::Prefab("Assets/Prefabs/DarkKnight.trp");

    p_Dunkleosteus = TerminaScript::Prefab("Assets/Prefabs/Dunkleosteus.trp");
    p_Eel = TerminaScript::Prefab("Assets/Prefabs/Eel.trp");
    p_Mermaid = TerminaScript::Prefab("Assets/Prefabs/Mermaid.trp");
    p_Kelpie = TerminaScript::Prefab("Assets/Prefabs/Kelpie.trp");

    p_RunicDeer = TerminaScript::Prefab("Assets/Prefabs/RunicDeer.trp");
    p_RedDragon = TerminaScript::Prefab("Assets/Prefabs/RedDragon.trp");

    characterPrefabMap["Diane"] = p_Diane;
    characterPrefabMap["Emilie"] = p_Emilie;
    characterPrefabMap["Claire"] = p_Claire;
    characterPrefabMap["Marcus"] = p_Marcus;
    characterPrefabMap["Brutus"] = p_Brutus;
    characterPrefabMap["Edward"] = p_Edward;
    characterPrefabMap["Alex"] = p_Alex;
    characterPrefabMap["Penelope"] = p_Penelope;

    characterPrefabMap["Rat"] = p_Rat;
    characterPrefabMap["Wolf"] = p_Wolf;
    characterPrefabMap["Hawk"] = p_Hawk;
    characterPrefabMap["Bear"] = p_Bear;

    characterPrefabMap["Ghost"] = p_Ghost;
    characterPrefabMap["Gargoyle"] = p_Gargoyle;
    characterPrefabMap["Skeleton"] = p_Skeleton;
    characterPrefabMap["Adept Of The Chaos"] = p_AdeptOfTheChaos;
    characterPrefabMap["DarkKnight"] = p_DarkKnight;

    characterPrefabMap["Dunkleosteus"] = p_Dunkleosteus;
    characterPrefabMap["Eel"] = p_Eel;
    characterPrefabMap["Mermaid"] = p_Mermaid;
    characterPrefabMap["Kelpie"] = p_Kelpie;

    characterPrefabMap["RunicDeer"] = p_RunicDeer;
    characterPrefabMap["RedDragon"] = p_RedDragon;

#pragma endregion
}

void Game::Update(float deltaTime)
{

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec4 BgColor = ImVec4(0.200f, 0.133f, 0.075f, 1.0f);
    ImVec4 ItemsColor = ImVec4(0.349f, 0.251f, 0.169f, 1.0f);

    ImVec4 normalColor  = ImVec4(0.231f, 0.153f, 0.086f, 1.0f);
    ImVec4 hoverColor   = ImVec4(0.212f, 0.133f, 0.071f, 1.0f);
    ImVec4 activeColor  = ImVec4(0.161f, 0.094f, 0.043f, 1.0f);

    switch (gameState)
    {

        case EGameState::Title : {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

            ImGui::Dummy(ImVec2(0,100));
            ImGui::SetWindowFontScale(5.f);
            std::string title = "ENDLESS ROGUE";
            float textWidth = ImGui::CalcTextSize(title.c_str()).x;
            float avail = ImGui::GetContentRegionAvail().x;
            ImGui::SetCursorPosX((avail - textWidth) * 0.5f);
            ImGui::Text("ENDLESS ROGUE");

            ImGui::Dummy(ImVec2(0,250));

            float buttonWidth = 120.0f;
            ImGui::SetCursorPosX((avail - buttonWidth) * 0.5f);
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("Play")) { gameState = EGameState::Menu; }
            ImGui::PopStyleColor(3);

            ImGui::End();
            ImGui::PopStyleColor();
            }
            break;

        case EGameState::Menu :
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

            ImGui::SetWindowFontScale(2.f);
            ImGui::Text("Select your characters");
            ImGui::SameLine();
            ImGui::BeginDisabled(!gameplay->teamIsComplete());
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("Launch Run")) {
                gameState = EGameState::Run;
            };
            ImGui::PopStyleColor(3);
            ImGui::EndDisabled();

            // ===== LAYOUT SIMPLE =====
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, viewport->Size.x / 5.0f + 0.0f);
            // ===== LEFT: LIST =====
            ImGui::SetWindowFontScale(1.5f);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ItemsColor);
            ImGui::BeginChild("CharacterList", ImVec2(viewport->Size.x / 2.0f , 0), true);
            for (int i = 0; i < allCharacters.size(); i++) {
                if (ImGui::Selectable(allCharacters[i]->getName().c_str(), selectedCharacter == i)) {
                    selectedCharacter = i;
                }
            }

            ImGui::Dummy(ImVec2(0,305));

            ImGui::SetWindowFontScale(1.5f);
            ImGui::Text("Character Selected :");

            ImGui::Dummy(ImVec2(0,10));

            for (int i = 0; i < gameplay->getActiveCharacters().size(); i++) {
                ImGui::Text("%s", gameplay->getActiveCharacters()[i]->getName().c_str());
            }

            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::NextColumn();

            // ===== RIGHT: DETAILS =====
            ImGui::SetWindowFontScale(3.f);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ItemsColor);
            ImGui::BeginChild("CharacterDetails", ImVec2(viewport->Size.x * 4.0f / 5.0f, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

            if (selectedCharacter != -1) {
                auto& character = allCharacters[selectedCharacter];

                ImGui::SetWindowFontScale(1.5f);
                ImGui::Text("Character: %s", character->getName().c_str());
                ImGui::Dummy(ImVec2(0,10));
                ImGui::Text("Level : %i", character->getLevel());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("XP : %.1f       XPNeeded : %.1f       %.2f %%", character->getCurrentXP(), character->getXPNeeded(), character->getCurrentXP() * 100 / character->getXPNeeded());
                ImGui::Dummy(ImVec2(0,10));

                ImGui::Text("Class : %s", character->getStringClass().c_str());
                ImGui::Dummy(ImVec2(0,20));
                ImGui::Text("Description : %s", character->getDescriptions().c_str());
                ImGui::Dummy(ImVec2(0,20));

                ImGui::Text("Statistics");
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();
                ImGui::GetWindowDrawList()->AddLine(ImVec2(p_min.x, p_max.y - 1),ImVec2(p_max.x, p_max.y - 1),IM_COL32(255, 255, 255, 255),1.0f );

                ImGui::Dummy(ImVec2(0,10));
                ImGui::Text("Health Point : %.0f", character->getMaxHealth());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Attack Damage : %.0f", character->getMaxAttackDamage());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Magic Damage : %.0f", character->getMaxAttackPower());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Armor : %.2f", character->getMaxArmor());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Magic Resistance : %.2f", character->getMaxPowerResist());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Speed : %.1f", character->getCurrentSpeed());
                ImGui::Dummy(ImVec2(0,20));

                ImGui::BeginDisabled(gameplay->isInTeam(character) or gameplay->teamIsComplete());
                ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
                if (ImGui::Button("Select")) {
                    gameplay->addToTeam(character);
                }
                ImGui::PopStyleColor(3);
               ImGui::EndDisabled();

                ImGui::BeginDisabled(!gameplay->isInTeam(character));
                ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
                if (ImGui::Button("UnSelect")) {
                    gameplay->removeFromTeam(character);
                }
                ImGui::PopStyleColor(3);
                ImGui::EndDisabled();
            }
            else {
                ImGui::Text("Select a character...");
            }

            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::Columns(1);
            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }
        case EGameState::Run :
            if (gameplay->teamIsComplete() && !runStarted) {
                drawCharacter();
                gameplay->setRunState(EGameRunState::STARTRUN);
                runStarted = true;
            }

        gameplay->gameloop();

            if (gameplay->getDestroyEnemy()) {
                cleanGameEntity(enemyActor);
                gameplay->setDestroyEnemy(false);
            }

            if (gameplay->getEnemySpawned())
            {
                drawEnemy();
                gameplay->setEnemySpawned(false);
            }
            if (gameplay->getDestroyCharacter()) {
                cleanGameEntity(gameActor);
                std::cout << "Character dead";
            }




            if (gameplay->getRunEnded())
            {
                gameState = EGameState::Menu;
                gameplay->setRunEnded(false);
                runStarted = false;
            }
            break;

        case EGameState::End :
            break;

        default:
            break;
    }

}


void Game::drawCharacter() {
    for (auto& character : gameplay->getActiveCharacters()) {
        auto it = characterPrefabMap.find(character->getName());
        if (it != characterPrefabMap.end()) {

            auto entityActor = Instantiate(it->second);
            entityActor->SetName(character->getName().c_str());
            gameActor.push_back(entityActor);

            for (auto& child : GetChildren()) {
                std::string name = child->GetName();
                if (name.find("Slot") != std::string::npos) {
                    size_t pos = name.find("Slot ");
                    int slotIndex = std::stoi(name.substr(pos + 5)) - 1;
                    if (slotIndex >= 0 && slotIndex < gameActor.size()) {
                        auto entity = gameActor[slotIndex];
                        glm::vec3 slotPos = child->GetComponent<Termina::Transform>().GetPosition();
                        entity->GetComponent<Termina::Transform>().SetPosition(glm::vec3(slotPos.x,entity->GetComponent<Termina::Transform>().GetPosition().y, slotPos.z));
                    }
                }
            }
        }
    }
}

void Game::drawEnemy() {
    if (!enemyActor.empty()) {
        cleanGameEntity(enemyActor);
    }
    for (auto& ennemi : gameplay->getEnemyVector()) {
        auto it = characterPrefabMap.find(ennemi->getName());
        if (it != characterPrefabMap.end())
        {
            auto entityActor = Instantiate(it->second);
            entityActor->SetName(ennemi->getName().c_str());
            enemyActor.push_back(entityActor);

            for (auto& child : GetChildren()) {
                std::string name = child->GetName();
                if (name.find("Enemy") != std::string::npos) {
                    size_t pos = name.find("Enemy ");
                    int slotIndex = std::stoi(name.substr(pos + 6)) - 1;
                    if (slotIndex >= 0 && slotIndex < enemyActor.size()) {
                        auto enemy = enemyActor[slotIndex];
                        glm::vec3 slotPos = child->GetComponent<Termina::Transform>().GetPosition();
                        enemy->GetComponent<Termina::Transform>().SetPosition(glm::vec3(slotPos.x,enemy->GetComponent<Termina::Transform>().GetPosition().y, slotPos.z));
                    }
                }
            }
        }
    }
}

void Game::cleanGameEntity(std::vector<Termina::Actor*>& _actor) {
    for (auto& entity : _actor) {
        Destroy(entity);
    }
    _actor.clear();
}
