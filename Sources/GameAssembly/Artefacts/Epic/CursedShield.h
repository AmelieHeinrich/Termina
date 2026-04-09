#pragma once
#include "../Artefact.h"

class CursedShield : public Artefact
{
public:
    CursedShield();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};