#pragma once
#include "../Artefact.h"

class WolfFur : public Artefact
{
public:
    WolfFur();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};