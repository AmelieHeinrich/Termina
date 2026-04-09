#pragma once
#include "../Artefact.h"

class ToeBone : public Artefact
{
public:
    ToeBone();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};