#pragma once
#include "../Artefact.h"

class GreatBearMedal : public Artefact
{
public:
    GreatBearMedal();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};