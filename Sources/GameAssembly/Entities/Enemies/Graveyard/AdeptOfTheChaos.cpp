#include "AdeptOfTheChaos.h"
#include "../../Characters/Character.h"

AdeptOfTheChaos::AdeptOfTheChaos(int floor) {
    name = "Adept Of The Chaos";
    entityClass = EClass::RANGEDDPS;
    description = "He's dark, his mind is tortured and he will avenge all of his losses.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 50.0f;

    baseHealth = 30.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 28.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 3.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 6.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 80.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1300.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void AdeptOfTheChaos::Start() {}

void AdeptOfTheChaos::Update(float deltaTime) {}

void AdeptOfTheChaos::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void AdeptOfTheChaos::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool AdeptOfTheChaos::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            if (secondAbilityUp) availableAbilities.push_back(2);
            if (thirdAbilityUp)  availableAbilities.push_back(3);
            if (fourthAbilityUp) availableAbilities.push_back(4);

            if (availableAbilities.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableAbilities.size() - 1);
            int choice = availableAbilities[distChoice(rng)];

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
                    thirdAbility();
                    break;
                }
            case 4:
                {
                    std::vector<Character*> targets;
                    for (auto& c : characters)
                    {
                        auto* t = dynamic_cast<Character*>(c.get());
                        if (t) targets.push_back(t);
                    }
                    fourthAbility(targets);
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

void AdeptOfTheChaos::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
    LogManager::getInstance().addLog("Adept of the Chaos attacks " + target.getName() + " with \"Black Thunder\".", ImVec4(240, 0.518, 0.518, 1));
}

void AdeptOfTheChaos::secondAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityTwo));
    LogManager::getInstance().addLog("Adept of the Chaos attacks " + target.getName() + " with \"Dark Orb\".", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void AdeptOfTheChaos::thirdAbility() {
    currentHealth = currentHealth - (maxHealth * 15.0f / 100.0f);
    currentAttackPower = currentAttackPower + (currentAttackPower * 10.0f / 100.0f);
    LogManager::getInstance().addLog("Adept of the Chaos casts \"Magic Coward Coat\", he looses HP and wins Attack Power bonus.", ImVec4(240, 0.518, 0.518, 1));

    CD3 = 4;
}

void AdeptOfTheChaos::fourthAbility(const std::vector<Character*>& targets) {
    for (auto& target : targets)
    {
        float dmgDealt = currentAttackPower * (1.0f - target->getCurrentPowerResist() / 100.0f);
        target->setCurrentHealth(std::max(0.0f, target->getCurrentHealth() - dmgDealt * powerAbilityFour));
        LogManager::getInstance().addLog("Adept of the Chaos attacks " + target->getName() + " with \"Rise of the Demons\".", ImVec4(240, 0.518, 0.518, 1));
    }

    CD4 = 7;
}

std::shared_ptr<Artefact> AdeptOfTheChaos::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Smoke Bomb !", ImVec4(1, 0, 0, 1));
        return std::make_shared<SmokeBomb>();
    }
    else if (roll < 15.f) {
        //return std::make_shared<ChaoticArmor>();
        return nullptr;
    }
    else if (roll < 17.f) {
        LogManager::getInstance().addLog("You obtained an Epic Artefact: Malicious Eye !", ImVec4(1, 0, 0, 1));
        return std::make_shared<MaliciousEye>();
    }
    else if (roll < 17.5f) {
        return nullptr;
    }
    return nullptr;
}