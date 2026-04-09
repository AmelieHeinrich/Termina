#pragma once
#include "../Artefact.h"

class KnightSBadge : public Artefact
{
public:
    KnightSBadge();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};