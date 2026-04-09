#include "BearSFoot.h"

BearSFoot::BearSFoot() {
    name = "Bear's Foot";
    description = "Heal 2% / artefact's level health of every damage dealt.";
    droppedBy = "Bear";
    quality = Quality::COMMON;
}

void BearSFoot::actingArtefact(Entity& target) {
}

void BearSFoot::onInflictedDamage(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * (2.0f * level) / 100.0f);
}

void BearSFoot::actingArtefactEveryTurns(Entity& target) {
}