#include "Mermaid.h"
#include "../../Characters/Character.h"

Mermaid::Mermaid(int floor) {
    name = "Mermaid";
    entityClass = EClass::SUPPORT;
    description = "A half-woman half-fish creature that enchants all beings that dare to approach.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 40.0f;

    baseHealth = 50.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0.0f;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 15.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 5.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 10.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1100.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Mermaid::Start() {}

void Mermaid::Update(float deltaTime) {}

void Mermaid::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Mermaid::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Mermaid::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        enemyState = EnemyState::ACTING;
        break;

    case EnemyState::ACTING:
        {
            if (characters.empty()) return false;

            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
            Character* target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            if (!target) return false;

            if (enemies.empty()) return false;

            std::uniform_int_distribution<int> distEnemy(0, enemies.size() - 1);
            Enemy* enemy1 = dynamic_cast<Enemy*>(enemies[distEnemy(rng)].get());

            if (!enemy1) return false;

            std::vector<int> availableChoices;

            if (firstAbilityUp)  availableChoices.push_back(1);
            if (secondAbilityUp) availableChoices.push_back(2);
            if (thirdAbilityUp) availableChoices.push_back(3);
            if (fourthAbilityUp) availableChoices.push_back(4);

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility(*target, enemies);
                break;
            case 3:
                thirdAbility(*enemy1);
                break;
            case 4:
                {
                    fourthAbility(enemies);
                    break;
                }
            default:
                break;
            }

            enemyState = EnemyState::ENDTURN;
            break;
        }

    case EnemyState::ENDTURN:
        endTurn();
        enemyState = EnemyState::STARTTURN;
        return true;
    }

    return false;
}

void Mermaid::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Mermaid attacks " + target.getName() + " with \"Water bubble\".", ImVec4(240, 0.518, 0.518, 1));
}

void Mermaid::secondAbility(Character& target, std::vector<std::shared_ptr<Entity>> enemies) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Mermaid attacks " + target.getName() + " with \"Cursed Melody\".", ImVec4(240, 0.518, 0.518, 1));

    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::uniform_int_distribution<int> distTarget(0, enemies.size() - 1);
    Enemy* targetEnemy = dynamic_cast<Enemy*>(enemies[distTarget(rng)].get());

    std::uniform_int_distribution<int> dist(1, 5);

    int choice = dist(rng);
    float debuff = 5.0f;

    if (choice == 1) {
        targetEnemy->setCurrentAttackDamage(std::max(0.0f, targetEnemy->getCurrentAttackDamage() + debuff));
        LogManager::getInstance().addLog(target.getName() + " takes Attack Damage bonus.", ImVec4(240, 0.518, 0.518, 1));
    }
    else if (choice == 2) {
        targetEnemy->setCurrentAttackPower(std::max(0.0f, targetEnemy->getCurrentAttackPower() + debuff));
        LogManager::getInstance().addLog(target.getName() + " takes Power Damage bonus.", ImVec4(240, 0.518, 0.518, 1));
    }
    else if (choice == 3) {
        targetEnemy->setCurrentArmor(std::max(0.0f, targetEnemy->getCurrentArmor() + debuff));
        LogManager::getInstance().addLog(target.getName() + " takes Armor bonus.", ImVec4(240, 0.518, 0.518, 1));
    }
    else if (choice == 4) {
        targetEnemy->setCurrentPowerResist(std::max(0.0f, targetEnemy->getCurrentPowerResist() + debuff));
        LogManager::getInstance().addLog(target.getName() + " takes Power Resist bonus.", ImVec4(240, 0.518, 0.518, 1));
    }
    else if (choice == 5) {
        targetEnemy->setCurrentSpeed(std::max(0.0f, targetEnemy->getCurrentSpeed() - debuff));
        LogManager::getInstance().addLog(target.getName() + " takes Speed bonus.", ImVec4(240, 0.518, 0.518, 1));
    }

    CD2 = 4;
}

void Mermaid::thirdAbility(Enemy& target) {
    target.resetStats();
    LogManager::getInstance().addLog("Mermaid uses \"Evil Attraction\". All " + target.getName() + "'bonuses are removed.", ImVec4(240, 0.518, 0.518, 1));

    CD3 = 5;
}

void Mermaid::fourthAbility(std::vector<std::shared_ptr<Entity>> enemies)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::uniform_int_distribution<int> dist(1, 5);
    float buff = 5.0f;

    for (auto& e : enemies)
    {
        Enemy* targetEnemy = dynamic_cast<Enemy*>(e.get());
        if (!targetEnemy) continue;

        int choice = dist(rng);

        switch (choice)
        {
        case 1:
            targetEnemy->setCurrentAttackDamage(targetEnemy->getCurrentAttackDamage() + buff);
            LogManager::getInstance().addLog("Mermaid uses \"Melancholic Aria\". " + targetEnemy->getName() + " takes Attack Damage bonus.", ImVec4(240, 0.518, 0.518, 1));
            break;

        case 2:
            targetEnemy->setCurrentAttackPower(targetEnemy->getCurrentAttackPower() + buff);
                LogManager::getInstance().addLog("Mermaid uses \"Melancholic Aria\". " + targetEnemy->getName() + " takes Attack Power bonus.", ImVec4(240, 0.518, 0.518, 1));
            break;

        case 3:
            targetEnemy->setCurrentArmor(targetEnemy->getCurrentArmor() + buff);
                LogManager::getInstance().addLog("Mermaid uses \"Melancholic Aria\". " + targetEnemy->getName() + " takes Armor bonus.", ImVec4(240, 0.518, 0.518, 1));
            break;

        case 4:
            targetEnemy->setCurrentPowerResist(targetEnemy->getCurrentPowerResist() + buff);
                LogManager::getInstance().addLog("Mermaid uses \"Melancholic Aria\". " + targetEnemy->getName() + " takes Power Resist bonus.", ImVec4(240, 0.518, 0.518, 1));
            break;

        case 5:
            targetEnemy->setCurrentSpeed(targetEnemy->getCurrentSpeed() + buff);
                LogManager::getInstance().addLog("Mermaid uses \"Melancholic Aria\". " + targetEnemy->getName() + " takes Speed bonus.", ImVec4(240, 0.518, 0.518, 1));
            break;

        default:
            break;
        }
    }

    CD4 = 7;
}

std::shared_ptr<Artefact> Mermaid::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        return nullptr;
    }
    else if (roll < 15.f) {
        return nullptr;
    }
    else if (roll < 17.f) {
        return nullptr;
    }
    else if (roll < 17.5f) {
        return nullptr;
    }
    return nullptr;
}