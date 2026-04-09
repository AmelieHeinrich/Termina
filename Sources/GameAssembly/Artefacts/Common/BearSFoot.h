#pragma once
#include "../Artefact.h"

class BearSFoot : public Artefact
{
public:
    BearSFoot();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};