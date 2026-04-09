#include "DarkKnight.h"
#include "../../Characters/Character.h"

DarkKnight::DarkKnight(int floor) {
    name = "DarkKnight";
    entityClass = EClass::TANK;
    description = "Riding his dark horse, the mysterious dark knight charges all that fight for the light.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 70.0f;
    finalPR = 70.0f;

    baseHealth = 110.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 20.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 10.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 15.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 12.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 80.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 35.0f;
    maxExpDrop = 1200.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void DarkKnight::Start() {}

void DarkKnight::Update(float deltaTime) {}

void DarkKnight::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void DarkKnight::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool DarkKnight::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        if (currentHealth < maxHealth * 1.0f / 4.0f) { thirdAbility(); }
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
                break;
            case 2:
                secondAbility(*target);
                break;
            case 3:
                fourthAbility(*target);
                break;
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

void DarkKnight::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Dark Knight attacks " + target.getName() + " with \"Sword Slash\".", ImVec4(240, 0.518, 0.518, 1));
}

void DarkKnight::secondAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Dark Knight attacks " + target.getName() + " with \"Shield Bash\".", ImVec4(240, 0.518, 0.518, 1));

    CD3 = 3;
}

void DarkKnight::thirdAbility() {
    currentArmor = currentArmor - (currentArmor * 20.0f / 100.0f);
    currentPowerResist = currentPowerResist - (currentPowerResist * 20.0f / 100.0f);

    currentAttackPower = currentAttackPower + (currentAttackPower * 20.0f / 100.0f);

    LogManager::getInstance().addLog("The passive \"Last Resort Rage\" of Dark Knight decrease their defensive stats and increase his Attack Power.", ImVec4(240, 0.518, 0.518, 1));
}

void DarkKnight::fourthAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityFour));
    LogManager::getInstance().addLog("Dark Knight attacks " + target.getName() + " with \"Shadow Rush\".", ImVec4(240, 0.518, 0.518, 1));

    CD3 = 7;
}

std::shared_ptr<Artefact> DarkKnight::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Knight's Badge !", ImVec4(1, 0, 0, 1));
        return std::make_shared<KnightSBadge>();
    }
    else if (roll < 15.f) {
        //return std::make_shared<KnightSHelmet>();
        return nullptr;
    }
    else if (roll < 17.f) {
        LogManager::getInstance().addLog("You obtained an Epic Artefact: Cursed Shield !", ImVec4(1, 0, 0, 1));
        return std::make_shared<CursedShield>();
    }
    else if (roll < 17.5f) {
        //return std::make_shared<DarkSword>();
        return nullptr;
    }
    return nullptr;
}