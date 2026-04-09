#include "RatTooth.h"

RatTooth::RatTooth() {
    name = "Rat Tooth";
    description = "Boost poison damage by 20% / artefact's level.";
    droppedBy = "Rat";
    quality = Quality::RARE;
}

void RatTooth::actingArtefact(Entity& target) {
    target.setPoisonMultiplier(1.2f * level);
}

void RatTooth::onInflictedDamage(Entity& target) {
}

void RatTooth::actingArtefactEveryTurns(Entity& target) {
}