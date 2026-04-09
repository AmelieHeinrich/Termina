#include "KnightSBadge.h"

KnightSBadge::KnightSBadge() {
    name = "Knight’s badge";
    description = "Improve generated shield by 5% / artefact's level.";
    droppedBy = "Dark knight";
    quality = Quality::COMMON;
}

void KnightSBadge::actingArtefact(Entity& target) {
    target.setGeneratedShield(target.getGeneratedShield() + target.getGeneratedShield() * 5.0f / 100.0f);
}

void KnightSBadge::onInflictedDamage(Entity& target) {
}

void KnightSBadge::actingArtefactEveryTurns(Entity& target) {
}