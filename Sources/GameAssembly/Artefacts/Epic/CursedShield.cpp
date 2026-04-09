#include "CursedShield.h"

CursedShield::CursedShield() {
    name = "Cursed shield";
    description = "The holder lose 2% / artefact's level max HP per turn, but increase AD by 3% / artefact's level.";
    droppedBy = "Dark knight";
    quality = Quality::EPIC;
}

void CursedShield::actingArtefact(Entity& target) {
}

void CursedShield::onInflictedDamage(Entity& target) {
}

void CursedShield::actingArtefactEveryTurns(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() - target.getMaxHealth() * (2.0f * level) / 100.0f);
    target.setCurrentAttackDamage(target.getMaxAttackDamage() * 1.0f + (3.0f * level) / 100.0f);
}