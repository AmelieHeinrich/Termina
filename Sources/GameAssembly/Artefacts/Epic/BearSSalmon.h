#pragma once
#include "../Artefact.h"

class BearSSalmon : public Artefact
{
public:
    BearSSalmon();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};