#include "RedDragon.h"

#include "../../../Artefacts/Epic/RattataSkull.h"
#include "../../Characters/Character.h"

RedDragon::RedDragon(int floor) {
    name = "RedDragon";
    entityClass = EClass::BOSS;
    description = "The Red Dragon is a terrific creature, feared for his burning blazing breath and his majestic shape. The legend says that no one has ever returned alive from his lair.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 70.0f;
    finalPR = 40.0f;

    baseHealth = 350.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 35.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 20.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 20;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 15;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 50.0f;
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

void RedDragon::Start() {}

void RedDragon::Update(float deltaTime) {}

void RedDragon::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void RedDragon::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool RedDragon::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

void RedDragon::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));

    target.setCurrentSpeed(target.getCurrentSpeed() + (target.getCurrentSpeed() * 15.0f / 100.0f));

    LogManager::getInstance().addLog("Red Dragon uses \"Tail Smash\". " + target.getName() + " takes damages and a Speed debuff.", ImVec4(240, 0.518, 0.518, 1));
}

void RedDragon::secondAbility(Character& target) {
    float multiplier = 1.0f;
    if (target.getIsBurnt() | target.getIsStun() | target.getIsPoisoned() | target.getIsTaunt()) multiplier = 1.5f; else multiplier = 1.0f;
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * multiplier));
    LogManager::getInstance().addLog("Red Dragon uses \"Hate Flame\". " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void RedDragon::thirdAbility() {
    currentAttackPower = currentAttackPower + (currentAttackPower * 5.0f / 100.0f);
    currentAttackDamage = currentAttackDamage + (currentAttackDamage * 5.0f / 100.0f);
    LogManager::getInstance().addLog("The passive \"Hell Territory\" of Red Dragon increase their offensive stats by 5%.", ImVec4(240, 0.518, 0.518, 1));
}

void RedDragon::fourthAbility(const std::vector<Character*>& targets) {
    for (auto character : targets) {
        float dmgDealt = currentAttackDamage * (1.0f - character->getCurrentArmor() / 100.0f);
        character->setCurrentHealth(std::max(0.0f, character->getCurrentHealth() - dmgDealt));

        character->setCurrentAttackDamage(character->getCurrentAttackDamage() - character->getCurrentAttackDamage() * 15.0f / 100.0f);
        character->setCurrentAttackPower(character->getCurrentAttackPower() - character->getCurrentAttackPower() * 15.0f / 100.0f);
        LogManager::getInstance().addLog("Red Dragon uses \"Grand Fire\". " + character->getName() + " takes damages and offensive debuffs.", ImVec4(240, 0.518, 0.518, 1));
    }

    CD4 = 7;
}

std::shared_ptr<Artefact> RedDragon::createDrop() {
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
        //return std::make_shared<EternalFlame>();
        return nullptr;
    }
    return nullptr;
}