#include "WolfTooth.h"

WolfTooth::WolfTooth() {
    name = "Wolf Tooth";
    description = "Improve attack by 2% / artefact's level.";
    droppedBy = "Wolf";
    quality = Quality::RARE;
}

void WolfTooth::actingArtefact(Entity& target) {
    target.setCurrentAttackDamage(target.getCurrentAttackDamage() + target.getCurrentAttackDamage() * 2.0f / 100.0f);
}

void WolfTooth::onInflictedDamage(Entity& target) {
}

void WolfTooth::actingArtefactEveryTurns(Entity& target) {
}