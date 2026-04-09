#pragma once
#include "../Artefact.h"

class RattataSkull : public Artefact
{
public:
    RattataSkull();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};