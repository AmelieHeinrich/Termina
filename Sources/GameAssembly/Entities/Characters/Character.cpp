#include "Character.h"
#include "../../Artefacts/Artefact.h"

Character::Character()
{
    abilitySelected = 0;

    level = 1;
    maxLevel = 50;

    XPNeededForLvl2 = 100;
    finalXPNeeded = 100000;
    currentXP = 0;
    XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (maxLevel - 1));

    currentState = PlayerState::STARTTURN;
}

bool Character::manageXP()
{
    if (currentXP >= XPNeeded)
    {
        currentXP -= XPNeeded;
        XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (maxLevel - 1));
        return true;
    }
    return false;
}

void Character::levelUp()
{
    float previousMaxHP = maxHealth;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth += maxHealth - previousMaxHP;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = maxAttackDamage;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = maxAttackPower;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = maxArmor;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = maxPowerResist;
}

void Character::endRun() {
    while (manageXP())
    {
        levelUp();
    }
}

void Character::addCurrentXP(float newXP) { currentXP += newXP; }

float Character::getCurrentXP() const {return currentXP;}
float Character::getXPNeeded() const { return XPNeeded; }

void Character::takeDamageEvent(Entity& target) {
    if (artefact) {
        artefact->onInflictedDamage(target);
    }
}

bool Character::getArtefactAlreadyUsed() { return artefactAlreadyUsed; }
void Character::setArtefactAlreadyUsed(bool value) { artefactAlreadyUsed = value; }

std::shared_ptr<Artefact> Character::getArtefact() const { return artefact; }
void Character::setArtefact(std::shared_ptr<Artefact> newArtefact) { artefact = newArtefact; }
