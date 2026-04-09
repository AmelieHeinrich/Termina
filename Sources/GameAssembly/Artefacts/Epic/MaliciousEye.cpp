#include "MaliciousEye.h"

MaliciousEye::MaliciousEye() {
    name = "Malicious Eye";
    description = "At the start of every turn, 5% chance / artefact's level to reduce the CD of every abilities by 1.";
    droppedBy = "Adept of the chaos";
    quality = Quality::EPIC;
}

void MaliciousEye::actingArtefact(Entity& target) {
}

void MaliciousEye::onInflictedDamage(Entity& target) {
}

void MaliciousEye::actingArtefactEveryTurns(Entity& target) {
    int chance = 5 * level;

    if (rand() % 100 < chance)
    {
        target.setCD1(std::max(0, target.getCD1() - 1));
        target.setCD2(std::max(0, target.getCD2() - 1));
        target.setCD3(std::max(0, target.getCD3() - 1));
        target.setCD4(std::max(0, target.getCD4() - 1));
    }
}