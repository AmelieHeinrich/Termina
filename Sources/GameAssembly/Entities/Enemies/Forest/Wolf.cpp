#include "Wolf.h"
#include "../../Characters/Character.h"

Wolf::Wolf(int floor) {
    name = "Wolf";
    entityClass = EClass::CLOSEDDPS;
    description = "While watching the Wolf never forget that he is not chasing alone.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 55.0f;
    finalPR = 35.0f;

    baseHealth = 50.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 18.f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0.0f;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 5;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 5;
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

void Wolf::Start() {}

void Wolf::Update(float deltaTime) {}

void Wolf::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Wolf::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Wolf::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        {
        startTurn();
        enemyState = EnemyState::ACTING;
        int numberOfWolf = countWolves(enemies);

        thirdAbility(numberOfWolf);
        break;
        }

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
                {
                    int numberOfWolf4 = countWolves(enemies);
                    fourthAbility(*target, numberOfWolf4);
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

void Wolf::firstAbility(Character& target) { // powerAbilityOne=0.9f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
    LogManager::getInstance().addLog("Wolf uses \"Claw\". " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
}

void Wolf::secondAbility(Character& target) { // powerAbilityTwo=1.1f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityTwo));
    LogManager::getInstance().addLog("Wolf uses \"Violent Bite\". " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void Wolf::thirdAbility(int numberOfWolf) { // While there is another wolf in the fight improve their speed and attack
    int allies = std::max(0, numberOfWolf - 1);

    float attackBuff = 1.0f + 0.05f * allies;
    float speedBuff  = 1.0f + 0.05f * allies;

    currentAttackDamage = maxAttackDamage * attackBuff;
    currentSpeed = baseSpeed * speedBuff;

    CD3 = 0;
}

void Wolf::fourthAbility(Character& target, int numberOfWolf) { // Every Wolf attack a target with claw
    int attacks = std::max(0, numberOfWolf);

    for (int i = 0; i < attacks; i++) {
        firstAbility(target);
        LogManager::getInstance().addLog(std::to_string(numberOfWolf) + " Wolf(s) uses \"Coordinate Attack\". " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
    }

    CD4 = 4;
}

int Wolf::countWolves(const std::vector<std::shared_ptr<Entity>>& enemies)
{
    int count = 0;
    for (auto& e : enemies)
    {
        if (e->getName() == "Wolf") count++;
    }
    return count;
}

std::shared_ptr<Artefact> Wolf::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Wolf Fur !", ImVec4(1, 0, 0, 1));
        return std::make_shared<WolfFur>();
    }
    else if (roll < 15.f) {
        LogManager::getInstance().addLog("You obtained a Rare Artefact: Wolf Tooth !", ImVec4(1, 0, 0, 1));
        return std::make_shared<WolfTooth>();
    }
    else if (roll < 17.f) {
        return nullptr;
    }
    else if (roll < 17.5f) {
        //return std::make_shared<AlphaMedal>();
        return nullptr;
    }
    return nullptr;
}