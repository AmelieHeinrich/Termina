#pragma once
#include "../Artefact.h"

class MaliciousEye : public Artefact
{
public:
    MaliciousEye();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};