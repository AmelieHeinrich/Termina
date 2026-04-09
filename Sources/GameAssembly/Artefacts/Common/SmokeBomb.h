#pragma once
#include "../Artefact.h"

class SmokeBomb : public Artefact
{
public:
    SmokeBomb();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};