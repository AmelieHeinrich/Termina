#pragma once
#include "../Artefact.h"

class RatTooth : public Artefact
{
public:
    RatTooth();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};