#include "RunicDeer.h"
#include "../../Characters/Character.h"

RunicDeer::RunicDeer(int floor) {
    name = "RunicDeer";
    entityClass = EClass::BOSS;
    description = "RunicDear's description.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 70.0f;

    baseHealth = 100.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 40.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.5f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.5f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 50.0f;
    maxExpDrop = 1700.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void RunicDeer::Start() {}

void RunicDeer::Update(float deltaTime) {}

void RunicDeer::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void RunicDeer::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool RunicDeer::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        thirdAbility();
        enemyState = EnemyState::ACTING;
        break;

    case EnemyState::ACTING:
        {
            if (characters.empty()) return false;

            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
            Character* target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            Enemy* targetEnemy = dynamic_cast<Enemy*>(enemies[distTarget(rng)].get());
            if (!target) return false;
            if (!targetEnemy) return false;

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
                secondAbility(*target, *targetEnemy);
                break;
            case 3:
                {
                    std::vector<Character*> targets;
                    for (auto& c : characters)
                    {
                        Character* t = dynamic_cast<Character*>(c.get());
                        if (t) targets.push_back(t);
                    }
                    fourthAbility(targets);
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

void RunicDeer::dropArtefacts() {

}

void RunicDeer::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Runic Dear uses \"Horn Leech\". " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
}

void RunicDeer::secondAbility(Character& target, Enemy& enemyTarget) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));

    enemyTarget.setCurrentSpeed(enemyTarget.getCurrentSpeed() + (target.getCurrentSpeed() * 15.0f / 100.0f));
    LogManager::getInstance().addLog("Runic Dear uses \"Savage Root\". " + target.getName() + " takes damages. " + target.getName() + " takes a Speed buff.", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void RunicDeer::thirdAbility() {
    currentArmor = currentArmor + (currentArmor * 5.0f / 100.0f);
    currentPowerResist = currentPowerResist + (currentPowerResist * 5.0f / 100.0f);
    LogManager::getInstance().addLog("The passive \"Forest King Aura's\" of Runic Dear increase their defensive stats by 5%.", ImVec4(240, 0.518, 0.518, 1));
}

void RunicDeer::fourthAbility(const std::vector<Character*>& targets) {
    for (auto character : targets) {
        float dmgDealt = currentAttackPower * (1.0f - character->getCurrentPowerResist() / 100.0f);
        character->setCurrentHealth(std::max(0.0f, character->getCurrentHealth() - dmgDealt));
        LogManager::getInstance().addLog("Runic Dear uses \"Green Ruler's Wrath\". " + character->getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
    }

    CD4 = 7;
}

std::shared_ptr<Artefact> RunicDeer::createDrop() {
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
        LogManager::getInstance().addLog("You obtained a Legendary Artefact: Forest Rune's !", ImVec4(1, 0, 0, 1));
        //return std::make_shared<ForestRuneS>();
        return nullptr;
    }
    return nullptr;
}