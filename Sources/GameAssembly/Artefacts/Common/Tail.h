#pragma once
#include "../Artefact.h"

class Tail : public Artefact
{
public:
    Tail();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};