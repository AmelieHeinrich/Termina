#include "EelSEye.h"

EelSEye::EelSEye() {
    name = "Eel's eye";
    description = "Increase resources drop (+1 / artefact's level).";
    droppedBy = "Eel";
    quality = Quality::COMMON;
}

void EelSEye::actingArtefact(Entity& target) {
    target.resourcesWon = target.resourcesWon + level;
}

void EelSEye::onInflictedDamage(Entity& target) {
}

void EelSEye::actingArtefactEveryTurns(Entity& target) {
}