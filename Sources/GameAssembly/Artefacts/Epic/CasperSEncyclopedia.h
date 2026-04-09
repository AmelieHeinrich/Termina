#pragma once
#include "../Artefact.h"

class CasperSEncyclopedia : public Artefact
{
public:
    CasperSEncyclopedia();

    void actingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void actingArtefactEveryTurns(Entity &target) override;
};