#include "Tail.h"

Tail::Tail() {
    name = "Tail";
    description = "Heal 1% / artefact's level of max HP every turn.";
    droppedBy = "Rat";
    quality = Quality::COMMON;
}

void Tail::actingArtefact(Entity& target) {
}

void Tail::onInflictedDamage(Entity& target) {
}

void Tail::actingArtefactEveryTurns(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * (1.0f * level) / 100.0f);
}