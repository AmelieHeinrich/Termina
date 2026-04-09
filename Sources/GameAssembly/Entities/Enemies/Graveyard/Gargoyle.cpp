#include "Gargoyle.h"
#include "../../Characters/Character.h"

Gargoyle::Gargoyle(int floor) {
    name = "Gargoyle";
    entityClass = EClass::BOSS;
    description = "Gargoyle, this monster of stone, inspiring fear, jumps on his enemies.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 30.0f;

    baseHealth = 320.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 30.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 30.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 18.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 18.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 100.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 500.0f;
    maxExpDrop = 5000.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Gargoyle::Start() {}

void Gargoyle::Update(float deltaTime) {}

void Gargoyle::startTurn() {
    firstAbilityUp = true;

    isPoisoned = false;
    isBurnt = false;
    isStun = false;
    isTaunt = false;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Gargoyle::endTurn() {
    isPoisoned = false;
    isBurnt = false;
    isStun = false;
    isTaunt = false;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

bool Gargoyle::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            std::vector<int> availableAbilities;

            if (firstAbilityUp)  availableAbilities.push_back(1);

            if (availableAbilities.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableAbilities.size() - 1);
            int choice = availableAbilities[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            default:
                break;
            }

            enemyState = EnemyState::ENDTURN;
            break;
        }

    case EnemyState::ENDTURN:
        endTurn();
        LogManager::getInstance().addLog("Dark Knight is immune to all status effects.", ImVec4(240, 0.518, 0.518, 1));
        enemyState = EnemyState::STARTTURN;
        return true;
    }

    return false;
}

void Gargoyle::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
    LogManager::getInstance().addLog("Gargoyle attacks " + target.getName() + " with \"Rapid Strikes\" two times.", ImVec4(240, 0.518, 0.518, 1));
}

void Gargoyle::secondAbility() {
}

void Gargoyle::thirdAbility() {
}

void Gargoyle::fourthAbility() {
}

std::shared_ptr<Artefact> Gargoyle::createDrop() {
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
    else if (roll < 17.6f) {
        //return std::make_shared<GargoyleSkull>();
    }
    return nullptr;
}