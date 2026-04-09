#include "WolfFur.h"

WolfFur::WolfFur() {
    name = "Wolf Fur";
    description = "Boost 1% / artefact's level armor + resist.";
    droppedBy = "Wolf";
    quality = Quality::COMMON;
}

void WolfFur::actingArtefact(Entity& target) {
    target.setCurrentPowerResist(target.getCurrentPowerResist() + target.getCurrentPowerResist() * (1.0f * level) / 100.0f);
    target.setCurrentArmor(target.getCurrentArmor() + target.getCurrentArmor() * (1.0f * level) / 100.0f);
}

void WolfFur::onInflictedDamage(Entity& target) {
}

void WolfFur::actingArtefactEveryTurns(Entity& target) {
}