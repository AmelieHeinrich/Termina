#include "Hawk.h"
#include "../../Characters/Character.h"

Hawk::Hawk(int floor) {
    name = "Hawk";
    entityClass = EClass::SUPPORT;
    description = "Hawk, an incredibly fast and dangerous bird, with sharp claws and aggressive behaviour.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 30.0f;

    baseHealth = 40.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 6.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 3;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 5;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 20.0f;
    maxExpDrop = 900.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Hawk::Start() {}

void Hawk::Update(float deltaTime) {}

void Hawk::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Hawk::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Hawk::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            Enemy* enemy2 = dynamic_cast<Enemy*>(enemies[distEnemy(rng)].get());

            if (!enemy1) return false;

            std::vector<int> availableChoices;

            if (firstAbilityUp)  availableChoices.push_back(1);
            if (secondAbilityUp) availableChoices.push_back(2);
            if (fourthAbilityUp) availableChoices.push_back(3);

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                thirdAbility(*enemy1);
                break;
            case 2:
                secondAbility(*enemy1);
                thirdAbility(*enemy1);
                break;
            case 3:
                {
                    while (enemy2 == enemy1 && enemies.size() > 1)
                    {
                        enemy2 = dynamic_cast<Enemy*>(enemies[distEnemy(rng)].get());
                    }
                    fourthAbility(*enemy1, *enemy2); //target de enemy random
                    thirdAbility(*enemy1);
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

void Hawk::firstAbility(Character& target) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> chance(1, 100);
    std::uniform_int_distribution<int> dist(1, 5);

    if (chance(rng) <= 10)
    {
        int choice = dist(rng);
        float debuff = 5.0f;

        if (choice == 1) {
            target.setCurrentAttackDamage(std::max(0.0f, target.getCurrentAttackDamage() - debuff));
            LogManager::getInstance().addLog("Hawk uses \"Peck\" and debuff " + target.getName() + "'s Attack Damage.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 2) {
            target.setCurrentAttackPower(std::max(0.0f, target.getCurrentAttackPower() - debuff));
            LogManager::getInstance().addLog("Hawk uses \"Peck\" and debuff " + target.getName() + "'s Attack Power.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 3) {
            target.setCurrentArmor(std::max(0.0f, target.getCurrentArmor() - debuff));
            LogManager::getInstance().addLog("Hawk uses \"Peck\" and debuff " + target.getName() + "'s Armor.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 4) {
            target.setCurrentPowerResist(std::max(0.0f, target.getCurrentPowerResist() - debuff));
            LogManager::getInstance().addLog("Hawk uses \"Peck\" and debuff " + target.getName() + "'s Power Resist.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 5) {
            target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() + debuff));
            LogManager::getInstance().addLog("Hawk uses \"Peck\" and debuff " + target.getName() + "'s Speed.", ImVec4(240, 0.518, 0.518, 1));
        }
    }
}

void Hawk::secondAbility(Enemy& target) {
    target.setCurrentAttackDamage(target.getCurrentAttackDamage() + target.getCurrentAttackDamage() * 0.10f);
    target.setCurrentSpeed(target.getCurrentSpeed() - target.getCurrentSpeed() * 0.10f);
    LogManager::getInstance().addLog("Hawk uses \"Hunter's Scream\" and buff " + target.getName() + "'s Attack Damage and Speed.", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 4;
}

void Hawk::thirdAbility(Enemy& target) {
    target.setCurrentHealth( target.getCurrentHealth() + target.getMaxHealth() * 0.05f);
    LogManager::getInstance().addLog("The passive \"Surprise Rabbit\" of Hawk heals " + target.getName() + " by 5%.", ImVec4(240, 0.518, 0.518, 1));
}

void Hawk::fourthAbility(Enemy& target1, Enemy& target2) {
    target1.setCurrentSpeed(target1.getCurrentSpeed() - target1.getCurrentSpeed() * 0.10f);
    target2.setCurrentSpeed(target2.getCurrentSpeed() - target2.getCurrentSpeed() * 0.10f);
    LogManager::getInstance().addLog("Hawk uses \"Hawk's Rush\" and buff " + target1.getName() + "'s and " + target2.getName() + "'s Speed by 10%.", ImVec4(240, 0.518, 0.518, 1));

    CD4 = 5;
}

std::shared_ptr<Artefact> Hawk::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        return nullptr;
    }
    else if (roll < 15.f) {
        //return std::make_shared<Feather>();
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