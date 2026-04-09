#include "GreatBearMedal.h"

GreatBearMedal::GreatBearMedal() {
    name = "Great Bear Medal";
    description = "Revive 1 time.";
    droppedBy = "Bear";
    quality = Quality::LEGENDARY;
}

void GreatBearMedal::actingArtefact(Entity& target) {
    target.setHasARevive(true);
}

void GreatBearMedal::onInflictedDamage(Entity& target) {
}

void GreatBearMedal::actingArtefactEveryTurns(Entity& target) {
}