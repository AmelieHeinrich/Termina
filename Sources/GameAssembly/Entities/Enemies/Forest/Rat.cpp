#include "Rat.h"

#include "../../../Artefacts/Epic/RattataSkull.h"
#include "../../Characters/Character.h"

Rat::Rat(int floor) {
    name = "Rat";
    entityClass = EClass::CLOSEDDPS;
    description = "The rat is a discreet animal, very close to humans.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 30.0f;

    baseHealth = 20.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 22.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 2.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 2.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 65.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 25.0f;
    maxExpDrop = 1000.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;

}

void Rat::Start() {}

void Rat::Update(float deltaTime) {}

void Rat::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Rat::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Rat::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

void Rat::firstAbility(Character& target) {
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
            LogManager::getInstance().addLog("Rat uses \"Crunch\" and debuff " + target.getName() + "'s Attack Damage. " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 2) {
            target.setCurrentAttackPower(std::max(0.0f, target.getCurrentAttackPower() - debuff));
            LogManager::getInstance().addLog("Rat uses \"Crunch\" and debuff " + target.getName() + "'s Attack Power. " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 3) {
            target.setCurrentArmor(std::max(0.0f, target.getCurrentArmor() - debuff));
            LogManager::getInstance().addLog("Rat uses \"Crunch\" and debuff " + target.getName() + "'s Armor. " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 4) {
            target.setCurrentPowerResist(std::max(0.0f, target.getCurrentPowerResist() - debuff));
            LogManager::getInstance().addLog("Rat uses \"Crunch\" and debuff " + target.getName() + "'s Power Resist. " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
        }
        else if (choice == 5) {
            target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() + debuff));
            LogManager::getInstance().addLog("Rat uses \"Crunch\" and debuff " + target.getName() + "'s Speed. " + target.getName() + " takes damages.", ImVec4(240, 0.518, 0.518, 1));
        }
    }

    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    if (target.getIsPoisoned()) { thirdAbility(target); }
}

void Rat::secondAbility(Character& target) {
    target.setIsPoisoned(true);
    LogManager::getInstance().addLog("Rat uses \"Poisonous Bite\". " + target.getName() + " is poisoned.", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void Rat::thirdAbility(Character& target) {
    float cd = target.getPoisonCD();
    float percent = 0;
    if (cd == 5) { percent = 15.0f; }
    if (cd == 4) { percent = 12.0f; }
    if (cd == 3) { percent = 8.0f; }
    if (cd == 2) { percent = 5.0f; }
    if (cd == 1) { percent = 3.0f; }
    float dmgDealt = target.getMaxHealth() * percent / 100.0f;
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("The passive \"Living Poison\" of Rat trigger the poison on " + target.getName() + ".", ImVec4(240, 0.518, 0.518, 1));
}

void Rat::fourthAbility(const std::vector<Character*>& targets) {
    for (Character* target : targets) {
        if (!target) continue;
        target->setIsPoisoned(true);
        float dmgDealt = currentAttackDamage * (1.0f - target->getCurrentArmor() / 100.0f);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

        if (target->getIsPoisoned()) { thirdAbility(*target); }
        LogManager::getInstance().addLog("Rat uses \"Rat Wave\". " + target->getName() + " takes damages and is poisoned.", ImVec4(240, 0.518, 0.518, 1));
    }

    CD4 = 5;
}

std::shared_ptr<Artefact> Rat::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Tail !", ImVec4(1, 0, 0, 1));
        return std::make_shared<Tail>();
    }
    else if (roll < 15.f) {
        LogManager::getInstance().addLog("You obtained a Rare Artefact: Rat tooth !", ImVec4(1, 0, 0, 1));
        return std::make_shared<RatTooth>();
    }
    else if (roll < 17.f) {
        LogManager::getInstance().addLog("You obtained an Epic Artefact: Rattata Skull !", ImVec4(1, 0, 0, 1));
        return std::make_shared<RattataSkull>();
    }
    else if (roll < 17.5f) {
        //return std::make_shared<RatEyeTalisman>();
        return nullptr;
    }
    return nullptr;
}