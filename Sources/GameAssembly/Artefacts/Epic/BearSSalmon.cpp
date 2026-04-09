#include "BearSSalmon.h"

BearSSalmon::BearSSalmon() {
    name = "Bear's salmon";
    description = "Heal 3% / artefact's level of max HP every turn.";
    droppedBy = "Bear";
    quality = Quality::EPIC;
}

void BearSSalmon::actingArtefact(Entity& target) {
}

void BearSSalmon::onInflictedDamage(Entity& target) {
}

void BearSSalmon::actingArtefactEveryTurns(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * (3.0f * level) / 100.0f);
}