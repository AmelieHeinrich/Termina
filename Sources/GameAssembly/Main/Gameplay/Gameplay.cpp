#include "../Gameplay/Gameplay.h"

#include <algorithm>

#include "../../Entities/Characters/Tank/Diane.h"
#include "../../Entities/Characters/Tank/Emilie.h"

#include "../../Entities/Enemies/Forest/Rat.h"
#include "../../Entities/Enemies/Forest/Wolf.h"
#include "../../Entities/Enemies/Forest/Bear.h"
#include "../../Entities/Enemies/Forest/Hawk.h"
#include "../../Entities/Enemies/Graveyard/Ghost.h"
#include "../../Entities/Enemies/Graveyard/AdeptOfTheChaos.h"
#include "../../Entities/Enemies/Graveyard/DarkKnight.h"
#include "../../Entities/Enemies/Graveyard/Skeleton.h"
#include "../../Entities/Enemies/Ocean/Kelpie.h"
#include "../../Entities/Enemies/Ocean/Dunkleosteus.h"
#include "../../Entities/Enemies/Ocean/Mermaid.h"
#include "../../Entities/Enemies/Ocean/Eel.h"

#include "../../Entities/Enemies/Forest/RunicDeer.h"
#include "../../Entities/Enemies/Forest/RedDragon.h"
#include "../../Entities/Enemies/Graveyard/Gargoyle.h"
#include "../../Entities/Enemies/Ocean/Whale.h"

Gameplay::Gameplay() {
    if (!enemyManager) {
        enemyManager = std::make_shared<EnemyManager>();
    }
    if (!inventory) {
        inventory = std::make_shared<Inventory>();
    }
    if (!playerXP) {
        playerXP = std::make_unique<PlayerXP>();
    }

    currentBiome = EBiome::GRAVEYARD;

}

void Gameplay::startRun() {
    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Diane>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Diane> diane = std::dynamic_pointer_cast<Diane>(*it);
        diane->startRun(activeCharacters);
    }

    for (auto chara: activeCharacters) {
        speedManagerVec.push_back(chara);
        aliveCharaVec.push_back(chara);
    }
    currentLevel = 1;
}

void Gameplay::startFight() {
    destroyEnemy = false;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> enemyIndex(1, 4);
    std::uniform_int_distribution<int> bossIndex(1, 2);
    switch (currentBiome) {
        case EBiome::FOREST :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Rat>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Wolf>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Bear>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Hawk>(currentLevel); }
                }
            }
            else {
                spawnBoss = false;
                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDeer>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Rat>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Wolf>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Bear>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Hawk>(currentLevel); }
                }
            }
            break;

        case EBiome::OCEAN :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Kelpie>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Dunkleosteus>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Mermaid>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Eel>(currentLevel); }
                }
            }
            else {
                spawnBoss = false;
                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDeer>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Kelpie>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Dunkleosteus>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Mermaid>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Eel>(currentLevel); }
                }
            }
            break;

        case EBiome::GRAVEYARD :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<AdeptOfTheChaos>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Ghost>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<DarkKnight>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Skeleton>(currentLevel); }
                }
            }
            else {
                spawnBoss = false;
                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDeer>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<AdeptOfTheChaos>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Ghost>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<DarkKnight>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Skeleton>(currentLevel); }
                }
            }
            break;

        default:
            break;
    }

    for (auto enemy : enemyManager->getEnemies()) { speedManagerVec.push_back(enemy);}

    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Emilie>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Emilie> emilie = std::dynamic_pointer_cast<Emilie>(*it);
        emilie->startFight(enemyManager->getEnemies());
    }

    std::sort(speedManagerVec.begin(), speedManagerVec.end(), [](const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) { return a->getCurrentSpeed() < b->getCurrentSpeed(); });
    enemySpawned = true;
}

void Gameplay::updateFight()
{
    if (speedManagerVec.empty())
        return;

    // Sécurité index
    if (currentEntityIndex >= speedManagerVec.size())
        currentEntityIndex = 0;
    inventory->checkArtefactsInventory();

    auto& entity = speedManagerVec[currentEntityIndex];

    bool finished = false;

        if (entity->getIsStun()) {
            finished = true;
        }

    if (!aliveCharaVec.empty() && !enemyManager->getEnemies().empty()) {
        finished = entity->entityTurn(aliveCharaVec, enemyManager->getEnemies());
    }

    if (finished)
    {
        std::cout << entity->getName() << " finished turn " << std::endl;

        // Passer au prochain
        currentEntityIndex++;

        if (currentEntityIndex >= speedManagerVec.size())
            currentEntityIndex = 0;

            for (auto& e : speedManagerVec) {
                if (e->getCurrentHealth() <= 0) {
                    LogManager::getInstance().addLog( e->getName() + " is dead.", ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                }
            }

            if (std::erase_if(speedManagerVec, [](const std::shared_ptr<Entity>& entity) { return entity->getCurrentHealth() <= 0; })) {
                std::sort(speedManagerVec.begin(), speedManagerVec.end(), [](const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) { return a->getCurrentSpeed() < b->getCurrentSpeed(); });
            }
            if (std::erase_if(aliveCharaVec, [](const std::shared_ptr<Entity>& entity) { return entity->getCurrentHealth() <= 0; })) {
                std::sort(speedManagerVec.begin(), speedManagerVec.end(), [](const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) { return a->getCurrentSpeed() < b->getCurrentSpeed(); });
            }
            for (auto& enemy : enemyManager->getEnemies())
            {
                if (enemy->getCurrentHealth() > enemy->getMaxHealth()) {
                    enemy->setCurrentHealth(enemy->getMaxHealth());
                }
                if (enemy->getCurrentHealth() <= 0) {

                    if (enemy->getHasARevive()) {
                        enemy->setCurrentHealth(enemy->getMaxHealth() / 2);
                        enemy->setHasARevive(false);
                        LogManager::getInstance().addLog(enemy->getName() + " revive !", ImVec4(0, 0, 0, 1));
                    }

                    std::shared_ptr<Enemy> e = std::dynamic_pointer_cast<Enemy>(enemy);

                    auto drop = e->createDrop();
                    if (drop != nullptr) {
                        inventory->addArtefact(drop);
                    }

                    float xpToAdd = e->getCurrentExpDrop() / 4;

                    for (auto& chara : aliveCharaVec) {
                        std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(chara);
                        c->addCurrentXP(xpToAdd);
                    }

                    playerXP->addCurrentXP(e->getCurrentExpDrop());
                }
            }
            if (std::erase_if(enemyManager->getEnemies(), [](const std::shared_ptr<Entity>& entity) { return entity->getCurrentHealth() <= 0; })) {
                std::sort(speedManagerVec.begin(), speedManagerVec.end(), [](const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) { return a->getCurrentSpeed() < b->getCurrentSpeed(); });
            }
        }
    if (enemyManager->getEnemies().empty()) {
        runState = EGameRunState::ENDFIGHT;
    }

    for (auto& chara : activeCharacters) {
        if (chara->getCurrentHealth() <= 0) chara->setCurrentHealth(0);
    }

    if (aliveCharaVec.size() == 0) {
        runState = EGameRunState::ENDRUN;
    }
}

void Gameplay::endFight() {
    destroyEnemy = true;
    enemyManager->clearEnemies();
    currentEntityIndex = 0;
    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Emilie>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Emilie> emilie = std::dynamic_pointer_cast<Emilie>(*it);
        emilie->endFight();
    }

    currentLevel++;

    if (currentLevel % 10 == 0) {
        spawnBoss = true;
    }

    biomeCount++;
    if (biomeCount == 10) {
        static std::mt19937 rng(rd());
        std::uniform_int_distribution<int> biomeIndex(1, 3);

        biomeCount = 0;
        int biomeChose = biomeIndex(rng);
        if (biomeChose == 1) { currentBiome = EBiome::FOREST; }
        else if (biomeChose == 2) { currentBiome = EBiome::OCEAN; }
        else if (biomeChose == 3) { currentBiome = EBiome::GRAVEYARD; }
    }
    enemySpawned = false;

}

void Gameplay::endRun() {
    for (auto& c : activeCharacters) {
        std::shared_ptr<Character> chara = std::dynamic_pointer_cast<Character>(c);
        chara->setArtefact(nullptr);
        chara->endRun();
    }
    ImGui::Begin("YOU LOOSE");

    if (ImGui::Button("Main Menu")) {
        runEnded = true;
    }

    ImGui::End();
}

void Gameplay::drawImGui() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec4 BgColor = ImVec4(0.200f, 0.133f, 0.075f, 1.0f);
    ImVec4 ItemsColor = ImVec4(0.349f, 0.251f, 0.169f, 1.0f);

    float logsWindowWidth = viewport->Size.x / 4.0f;

    // ENEMY
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x - logsWindowWidth, viewport->Size.y / 8.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
    ImGui::Begin("Enemies Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::Columns(4, nullptr, true);

    auto& enemies = enemyManager->getEnemies();

    for (int i = 0; i < enemies.size(); i++)
    {
        auto& enemy = enemies[i];

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ItemsColor);
        ImGui::BeginChild(("Enemy" + std::to_string(i)).c_str(), ImVec2(-1, 70), true);

        ImGui::Text("Character: %s", enemy->getName().c_str());
        ImGui::SameLine(150);
        ImGui::Text("HP : %.2f", enemy->getCurrentHealth());
        ImGui::Dummy(ImVec2(0,5));
        ImGui::Text("Class : %s", enemy->getStringClass().c_str());
        if (enemy->getIsPoisoned()) {
            ImGui::SameLine(380);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(36, 10, 51, 255)), "Poisoned");
        }
        if (enemy->getIsBurnt()) {
            ImGui::SameLine(330);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(255, 108, 0, 255)), "Burn");
        }
        if (enemy->getIsStun()) {
            ImGui::SameLine(280);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(128, 128, 128, 255)), "Stun");
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();

        if ((i + 1) % 4 != 0)
            ImGui::NextColumn();
    }

    ImGui::Columns(1);
    ImGui::End();
    ImGui::PopStyleColor();

    // CHARA
    ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y * 2.0f / 3.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y * 1.0f / 3.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
    ImGui::Begin("Characters Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::Columns(4, nullptr, true);

    auto& characters = activeCharacters;

    for (int i = 0; i < characters.size(); i++)
    {
        auto& chara = characters[i];

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ItemsColor);
        ImGui::BeginChild(("Character" + std::to_string(i)).c_str(), ImVec2(-1, -1), true);

        ImGui::Text("Character: %s", chara->getName().c_str());
        ImGui::SameLine(330);
        ImGui::Text("HP : %.2f", chara->getCurrentHealth());
        ImGui::Dummy(ImVec2(0,5));
        ImGui::Text("Statistics");
        ImVec2 p_min = ImGui::GetItemRectMin();
        ImVec2 p_max = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddLine(ImVec2(p_min.x, p_max.y - 1),ImVec2(p_max.x, p_max.y - 1),IM_COL32(255, 255, 255, 255),1.0f );

        if (chara->getIsPoisoned()) {
            ImGui::SameLine(380);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(36, 10, 51, 255)), "Poisoned");
        }
        if (chara->getIsBurnt()) {
            ImGui::SameLine(330);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(255, 108, 0, 255)), "Burn");
        }
        if (chara->getIsStun()) {
            ImGui::SameLine(280);
            ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(IM_COL32(128, 128, 128, 255)), "Stun");
        }

        ImGui::Dummy(ImVec2(0,10));
        ImGui::Text("Attack Damage : %.2f", chara->getCurrentAttackDamage());
        ImGui::Text("Magic Damage : %.2f", chara->getCurrentAttackPower());
        ImGui::Text("Armor : %.2f", chara->getCurrentArmor());
        ImGui::Text("Magic Resistance : %.2f", chara->getCurrentPowerResist());
        ImGui::Text("Speed : %.2f", chara->getCurrentSpeed());
        ImGui::Dummy(ImVec2(0,5));
        std::shared_ptr<Character> c = static_pointer_cast<Character>(chara);
        if (c->getArtefact() != nullptr) {
            ImGui::Text("Artefact : %s", c->getArtefact()->getName().c_str());
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();

        if ((i + 1) % 4 != 0)
            ImGui::NextColumn();
    }

    ImGui::Columns(1);
    ImGui::End();
    ImGui::PopStyleColor();

    // Vector Speed

    ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y / 8.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 10.0f, viewport->Size.y * 1.0f / 3.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
    ImGui::Begin("Entity Turn Order", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    for (const auto& e : speedManagerVec) {
        float textWidth = ImGui::CalcTextSize(e->getName().c_str()).x;
        float avail = ImGui::GetContentRegionAvail().x;
        ImGui::SetCursorPosX((avail - textWidth) * 0.5f);
        ImGui::Text("%s", e->getName().c_str());
        ImGui::Separator();
    }

    ImGui::End();
    ImGui::PopStyleColor();

    // Inventory

    if (!aliveCharaVec.empty()) { inventory->drawArtefactsInventory(aliveCharaVec); }
}

void Gameplay::gameloop()
{
    bool finished = false;

    switch (runState) {
        case EGameRunState::STARTRUN :
            startRun();
            playerXP->startRun();
            runState = EGameRunState::CHECKUPGRADE;
            break;

        case EGameRunState::CHECKUPGRADE : {
            finished = playerXP->upgradeSystem(currentLevel, activeCharacters);
            if (finished) runState = EGameRunState::STARTFIGHT;
            }
            break;

        case EGameRunState::STARTFIGHT :
            startFight();
            std::cout << "Fight started" << std::endl;
            playerXP->applyBonuses(aliveCharaVec);
            LogManager::getInstance().addSeparator();
            LogManager::getInstance().addSeparator();
            LogManager::getInstance().addLog("New Fight");
            runState = EGameRunState::UPDATEFIGHT;
            break;

        case EGameRunState::UPDATEFIGHT :
            updateFight();
            drawImGui();
            LogManager::getInstance().drawImGui();
            break;

        case EGameRunState::ENDFIGHT :
            endFight();
            runState = EGameRunState::CHECKUPGRADE;
            break;

        case EGameRunState::ENDRUN :
            endRun();
            break;
    }
}

bool Gameplay::hasSameType(const Entity& entity) const
{
    return std::any_of(activeCharacters.begin(), activeCharacters.end(),
        [&entity](const std::shared_ptr<Entity>& e) {
            return typeid(*e) == typeid(entity);
        });
}

void Gameplay::addToTeam(const std::shared_ptr<Entity>& entity) {
    if (!entity) {
        std::cout << "Invalid entity\n";
        return;
    }

    if (activeCharacters.size() > 3 ) {
        std::cout << "Team Max Size Reached" << std::endl;
        return;
    }

    if (hasSameType(*entity)) {
        std::cout << entity->getName() << " is already in the team\n";
        return;
    }
    activeCharacters.push_back(entity);
    std::cout << entity->getName() << " added to team" << std::endl;
}

void Gameplay::removeFromTeam(const std::shared_ptr<Entity>& entity)
{
    if (!entity) {
        std::cout << "Invalid entity\n";
        return;
    }

    auto it = std::find(activeCharacters.begin(), activeCharacters.end(), entity);

    if (it == activeCharacters.end()) {
        std::cout << entity->getName() << " not in team\n";
        return;
    }

    activeCharacters.erase(it);
    std::cout << entity->getName() << " remove from team" << std::endl;
}


////////// Check if Team is Complete or If the character is already in team
bool Gameplay::teamIsComplete() {
    if (activeCharacters.size() == 4) {
        return true;
    }
    return false;
}

bool Gameplay::isInTeam(const std::shared_ptr<Entity> &entity) {
    auto it = std::find(activeCharacters.begin(), activeCharacters.end(), entity);
    if (it != activeCharacters.end()) {
        return true;
    }
    return false;
}

void Gameplay::setRunState(EGameRunState newState) { runState = newState; }
void Gameplay::setRunEnded(bool gameEnded) { runEnded = gameEnded; }

bool Gameplay::getRunEnded() const { return runEnded; }




bool Gameplay::setEnemySpawned(bool newBool)
{
    enemySpawned = newBool;
    return enemySpawned;
}

bool Gameplay::setDestroyCharacter(bool newBool) {
    destroyCharacter = newBool;
    return destroyCharacter;
}

bool Gameplay::setDestroyEnemy(bool newBool) {
    destroyEnemy = newBool;
    return destroyEnemy;
}

