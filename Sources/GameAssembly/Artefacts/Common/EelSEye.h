#pragma once
#include "../Artefact.h"

class EelSEye : public Artefact
{
public:
    EelSEye();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};