#include "Whale.h"
#include "../../Characters/Character.h"

Whale::Whale(int floor) {
    name = "Whale";
    entityClass = EClass::BOSS;
    description = "Since its birth, this Whale has been raised in a bathtub, fusing with it. Its sometimes difficult to know if it does or not part of its body.";
    biome = Biome::OCEAN;

    level = floor;
    landing = floor / 5;

    finalArmor = 60.0f;
    finalPR = 60.0f;

    baseHealth = 420.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 20.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 18.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 25.0f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 25.0f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 50.0f;
    maxExpDrop = 1600.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Whale::Start() {}

void Whale::Update(float deltaTime) {}

void Whale::startTurn() {
    firstAbilityUp = true;
    secondAbilityUp = true;
}

void Whale::endTurn() {
    manageStatusEffect();
}

bool Whale::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1: {
                std::vector<Character*> targets;
                for (auto& c : characters)
                {
                    Character* t = dynamic_cast<Character*>(c.get());
                    if (t) targets.push_back(t);
                }
                firstAbility(targets);
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
        std::vector<Enemy*> targets;
        for (auto& e : enemies)
        {
            Enemy* t = dynamic_cast<Enemy*>(e.get());
            if (t) targets.push_back(t);
        }
        secondAbility(targets);
        enemyState = EnemyState::STARTTURN;
        return true;
    }

    return false;
}

void Whale::firstAbility(const std::vector<Character*>& targets) {
    for (auto& target : targets) {
        float dmgDealt = currentAttackPower * (1.0f - target->getCurrentPowerResist() / 100.0f);
        target->setCurrentHealth(std::max(0.0f, target->getCurrentHealth() - dmgDealt));
        LogManager::getInstance().addLog("Whale attacks "+ target->getName() + " with \"Ocean wave\".", ImVec4(240, 0.518, 0.518, 1));
    }
}

void Whale::secondAbility(const std::vector<Enemy*>& targets) {
    for (auto& target : targets) {
        target->setCurrentHealth(target->getCurrentHealth() + target->getMaxHealth() * 5.0f / 100.0f);
        LogManager::getInstance().addLog("Whale heals "+ target->getName() + " by 5% her passive with \"Ocean Call\".", ImVec4(240, 0.518, 0.518, 1));
    }
}

void Whale::thirdAbility(Enemy& target) {
}

void Whale::fourthAbility(std::vector<std::shared_ptr<Entity>> enemies){
}

std::shared_ptr<Artefact> Whale::createDrop() {
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
        //return std::make_shared<ScaleOfTheWhale>();
        return nullptr;
    }
    return nullptr;
}