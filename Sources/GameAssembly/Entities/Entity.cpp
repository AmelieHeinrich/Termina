
#include "Entity.h"

Entity::Entity()
{
    CD1 = 0;
    CD2 = 0;
    CD3 = 0;
    CD4 = 0;

    hasARevive = false;
    isPoisoned = false;
    isBurnt = false;
    isTaunt = false;
    isStun = false;

    poisonMultiplier = 1.0f;
}

void Entity::manageStatusEffect()
{
    if (isPoisoned)
    {
        if (poisonCD == 5) {
            currentHealth -= maxHealth * (15 / 100 * poisonMultiplier);
            poisonCD--;
        }
        else if (poisonCD == 4) {
            currentHealth -= maxHealth * (12 / 100 * poisonMultiplier);
            poisonCD--;
        }
        else if (poisonCD == 3) {
            currentHealth -= maxHealth * (8 / 100 * poisonMultiplier);
            poisonCD--;
        }
        else if (poisonCD == 2) {
            currentHealth -= maxHealth * (5 / 100 * poisonMultiplier);
            poisonCD--;
        }
        else if (poisonCD == 1) {
            currentHealth -= maxHealth * (3 / 100 * poisonMultiplier);
            poisonCD--;
            isPoisoned = false;
        }
        LogManager::getInstance().addLog(this->getName() + " takes damages from the poison !", ImVec4(0.141f, 0.039f, 0.200f, 1.0f));
    }

    if (isBurnt)
    {
        if (burnCD == 3) {
            currentHealth -= maxHealth * (15 / 100);
            burnCD--;
        }
        else if (burnCD == 2) {
            currentHealth -= maxHealth * (10 / 100);
            burnCD--;
        }
        else if (burnCD == 1) {
            currentHealth -= maxHealth * (5 / 100);
            isBurnt = false;
            burnCD--;
        }
        LogManager::getInstance().addLog(this->getName() + " takes damages from its burn !", ImVec4(1.0f, 0.2f, 0.0f, 1.0f));
    }

    if (isTaunt)
    {
        if (tauntCD == 3) {
            tauntCD--;
        }
        else if (tauntCD == 2) {
            tauntCD--;
        }
        else if (tauntCD == 1) {
            tauntCD--;
            isTaunt = false;
        }
        LogManager::getInstance().addLog(this->getName() + " is taunt !", ImVec4(1.0f, 0.6f, 0.0f, 1.0f));
    }

    if (isStun) {
        isStun = false;
        LogManager::getInstance().addLog(this->getName() + " is stun !", ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
    }
}

void Entity::resetStats() {
    currentHealth = maxHealth;
    currentAttackPower = maxAttackPower;
    currentAttackDamage = maxAttackDamage;
    currentArmor = maxArmor;
    currentPowerResist = maxPowerResist;
    currentSpeed = baseSpeed;
    artefactAlreadyUsed = false;
    poisonMultiplier = 1.0f;
}

#pragma region Getters

std::string Entity::getName() const { return name; }
std::string Entity::getStringClass() const {
    switch (entityClass) {
        case EClass::CLOSEDDPS :
            return "Close DPS";
        case EClass::RANGEDDPS :
            return "Range DPS";
        case EClass::TANK :
            return "Tank";
        case EClass::SUPPORT :
            return "Support";
        default :
            return "Unknown";
    }
}
std::string Entity::getDescriptions() const { return description; }

int Entity::getLevel() const { return level; }

float Entity::getCurrentHealth() const { return currentHealth; }
float Entity::getShield() const { return shield; }
float Entity::getCurrentAttackDamage() const { return currentAttackDamage; }
float Entity::getCurrentAttackPower() const { return currentAttackPower; }
float Entity::getCurrentArmor() const { return currentArmor; }
float Entity::getCurrentPowerResist() const { return currentPowerResist; }
float Entity::getCurrentSpeed() const { return currentSpeed; }

float Entity::getMaxHealth() const { return maxHealth; }
float Entity::getMaxAttackDamage() const { return maxAttackDamage; }
float Entity::getMaxAttackPower() const { return maxAttackPower; }
float Entity::getMaxArmor() const { return maxArmor; }
float Entity::getMaxPowerResist() const { return maxPowerResist; }

int Entity::getCD1() const { return CD1; }
int Entity::getCD2() const { return CD2; }
int Entity::getCD3() const { return CD3; }
int Entity::getCD4() const { return CD4; }

int Entity::getPoisonCD() const { return poisonCD; }
int Entity::getBurnCD() const { return burnCD; }
int Entity::getTauntCD() const { return tauntCD; }

bool Entity::getFirstAbilityUp() const { return firstAbilityUp; }
bool Entity::getSecondAbilityUp() const { return secondAbilityUp; }
bool Entity::getThirdAbilityUp() const { return thirdAbilityUp; }
bool Entity::getFourthAbilityUp() const { return fourthAbilityUp; }

bool Entity::getIsPoisoned() const { return isPoisoned; }
bool Entity::getIsBurnt() const { return isBurnt; }
bool Entity::getIsTaunt() const { return isTaunt; }
bool Entity::getIsStun() const { return isStun; }
bool Entity::getIsDead() const { return isDead; }

EClass Entity::getClass() const { return entityClass; }

float Entity::getGeneratedShield() const { return generatedShield; }

bool Entity::getHasARevive() { return hasARevive; }

#pragma endregion

#pragma region Setters

void Entity::setCurrentHealth(float const newHealth) { currentHealth = newHealth; }
void Entity::setShield(float const newShield) { shield = newShield; }
void Entity::setCurrentAttackDamage(float const newDamage) { currentAttackDamage = newDamage; }
void Entity::setCurrentAttackPower(float const newPower) { currentAttackPower = newPower; }
void Entity::setCurrentArmor(float const newArmor) { currentArmor = newArmor; }
void Entity::setCurrentPowerResist(float const newPowerResist) { currentPowerResist = newPowerResist; }
void Entity::setCurrentSpeed(float const newSpeed) { currentSpeed = newSpeed; }

void Entity::setCD1(int const newCD1) { CD1 = newCD1; }
void Entity::setCD2(int const newCD2) { CD2 = newCD2; }
void Entity::setCD3(int const newCD3) { CD3 = newCD3; }
void Entity::setCD4(int const newCD4) { CD4 = newCD4; }

void Entity::setPoisonCD(int const newPoisonCD) { poisonCD = newPoisonCD; }
void Entity::setBurnCD(int const newBurnCD) { burnCD = newBurnCD; }
void Entity::setTauntCD(int const newTauntCD) { tauntCD = newTauntCD; }

void Entity::setIsPoisoned(bool const newIsPoisoned) { isPoisoned = newIsPoisoned; }
void Entity::setIsBurnt(bool const newIsBurnt) { isBurnt = newIsBurnt; }
void Entity::setIsTaunt(bool const newIsTaunt) { isTaunt = newIsTaunt; }
void Entity::setIsStun(bool const newIsStun) { isStun = newIsStun; }
void Entity::setIsDead(bool const newIsDead) { isDead = newIsDead; }

void Entity::setGeneratedShield(float newShield) { generatedShield = newShield; }
void Entity::setHasARevive(bool _hasARevive) { hasARevive = _hasARevive; }

void Entity::setLevel(int newLevel) { level = newLevel; }

void Entity::setPoisonMultiplier(float newPoisonMultiplier) { poisonMultiplier = newPoisonMultiplier; }

#pragma endregion
