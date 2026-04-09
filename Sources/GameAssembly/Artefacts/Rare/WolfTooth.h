#pragma once
#include "../Artefact.h"

class WolfTooth : public Artefact
{
public:
    WolfTooth();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};