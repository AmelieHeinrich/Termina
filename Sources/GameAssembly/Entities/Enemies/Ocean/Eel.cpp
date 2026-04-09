#include "Eel.h"
#include "../../Characters/Character.h"

Eel::Eel(int floor) {
    name = "Eel";
    entityClass = EClass::CLOSEDDPS;
    description = "A sneaky fish slipping away when caught.";
    biome = Biome::OCEAN;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 40.0f;

    baseHealth = 35.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 8.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 28.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 3.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 5.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 50.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 20.0f;
    maxExpDrop = 1000.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Eel::Start() {}

void Eel::Update(float deltaTime) {}

void Eel::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Eel::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Eel::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
                secondAbility();
                break;
            case 3:
                thirdAbility();
                break;
            case 4:
                {
                    fourthAbility(*target);
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

void Eel::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Eel attacks " + target.getName() + " with \"Electric Charge\".", ImVec4(240, 0.518, 0.518, 1));

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> proc(1, 100);

    if (proc(rng) <= 30) {
        float slow = 10.0f;
        target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() - slow));
        LogManager::getInstance().addLog(target.getName() + " takes a Speed malus.", ImVec4(240, 0.518, 0.518, 1));
    }
}

void Eel::secondAbility() {
    float buff = currentAttackDamage * 0.2f;
    currentAttackDamage += buff;
    LogManager::getInstance().addLog("Eel uses \"Charge Up\". He takes Attack Damage bonus.", ImVec4(240, 0.518, 0.518, 1));
    CD2 = 4;
}

void Eel::thirdAbility() {
    poisonCD = 0;
    isPoisoned = false;
    burnCD = 0;
    isBurnt = false;
    tauntCD = 0;
    isTaunt = false;
    isStun = false;
    LogManager::getInstance().addLog("Eel uses \"Slippery Mucus\". He removes all status effects to himself.", ImVec4(240, 0.518, 0.518, 1));

    CD3 = 5;
}

void Eel::fourthAbility(Character& target) {
    float multiplier = (target.getCurrentHealth() < target.getMaxHealth() * 0.5f) ? 2.5f : 1.5f;
    float dmgDealt = currentAttackPower * multiplier * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    LogManager::getInstance().addLog("Eel attacks " + target.getName() + " with \"Lightning Embrace\".", ImVec4(240, 0.518, 0.518, 1));
    CD4 = 6;
}

std::shared_ptr<Artefact> Eel::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Eel's Eye !", ImVec4(1, 0, 0, 1));
        return std::make_shared<EelSEye>();
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