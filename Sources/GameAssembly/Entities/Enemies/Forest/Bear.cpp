#include "Bear.h"
#include "../../Characters/Character.h"

Bear::Bear(int floor) {
    name = "Bear";
    entityClass = EClass::TANK;
    description = "Bear, a monstrous predator, feared by everyone. Do not touch his food or you'll regret it.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 80.0f;
    finalPR = 60.0f;

    baseHealth = 100.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 12.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 12.f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 10.f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 100.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1200.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Bear::Start() {}

void Bear::Update(float deltaTime) {}

void Bear::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Bear::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }
    std::cout << CD2 << std::endl;

    manageStatusEffect();
}

bool Bear::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            Character* target = nullptr;

            for (auto& c : characters)
            {
                Character* t = dynamic_cast<Character*>(c.get());
                if (t && t->getClass() == EClass::TANK)
                {
                    target = t;
                    break;
                }
            }

            if (!target)
            {
                std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
                target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            }

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
                secondAbility();
                break;
            case 3:
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

void Bear::firstAbility(Character& target) { // powerAbilityOne=0.9f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
    LogManager::getInstance().addLog("Bear attacks " + target.getName() + " with \"Claw\".", ImVec4(240, 0.518, 0.518, 1));
}

void Bear::secondAbility() {
    currentHealth = currentHealth + maxHealth * 0.15f;
    LogManager::getInstance().addLog("Bear heals by 15% with \"Surprise Salmon\".", ImVec4(240, 0.518, 0.518, 1));

    CD2 = 3;
}

void Bear::thirdAbility() {
    // done in entityTurn
}

void Bear::fourthAbility(Character& target) {
    currentArmor = currentArmor + currentArmor * 0.05f;
    currentPowerResist = currentPowerResist + currentPowerResist * 0.05f;

    target.setIsTaunt(true);
    setTauntCD(3);

    LogManager::getInstance().addLog("Bear uses \"I Am The King\", increasing its Defense and Resistance. " + target.getName() + " is taunt.", ImVec4(240, 0.518, 0.518, 1));

    CD4 = 7;
}

std::shared_ptr<Artefact> Bear::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        LogManager::getInstance().addLog("You obtained a Common Artefact: Bear's Foot !", ImVec4(1, 0, 0, 1));
        return std::make_shared<BearSFoot>();
    }
    else if (roll < 15.f) {
        return nullptr;
    }
    else if (roll < 17.f) {
        LogManager::getInstance().addLog("You obtained an Epic Artefact: Bear's Salmon !", ImVec4(1, 0, 0, 1));
        return std::make_shared<BearSSalmon>();
    }
    else if (roll < 17.5f) {
        LogManager::getInstance().addLog("You obtained a Legendary Artefact: Great Bear Medal !", ImVec4(1, 0, 0, 1));
        return std::make_shared<GreatBearMedal>();
    }
    return nullptr;
}