#include "ToeBone.h"

ToeBone::ToeBone() {
    name = "Toe Bone";
    description = "increase Resist by 2% / artefact's level.";
    droppedBy = "Skeleton";
    quality = Quality::COMMON;
}

void ToeBone::actingArtefact(Entity& target) {
    target.setCurrentPowerResist(target.getCurrentPowerResist() + target.getCurrentPowerResist() * (2.0f * level) / 100.0f);
}

void ToeBone::onInflictedDamage(Entity& target) {
}

void ToeBone::actingArtefactEveryTurns(Entity& target) {
}