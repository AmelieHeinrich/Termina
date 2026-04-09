#include "SmokeBomb.h"

SmokeBomb::SmokeBomb() {
    name = "Smoke Bomb";
    description = "Improve speed by 2% / artefact's level.";
    droppedBy = "Adept of the chaos";
    quality = Quality::COMMON;
}

void SmokeBomb::actingArtefact(Entity& target) {
    target.setCurrentSpeed(target.getCurrentSpeed() + target.getCurrentSpeed() * (2.0f * level) / 100.0f);
}

void SmokeBomb::onInflictedDamage(Entity& target) {
}

void SmokeBomb::actingArtefactEveryTurns(Entity& target) {
}