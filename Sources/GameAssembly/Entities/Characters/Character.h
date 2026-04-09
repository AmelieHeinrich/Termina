#pragma once
#include "../Entity.h"
#include "../../../ThirdParty/ImGui/imgui.h"
#include "../../../ThirdParty/ImGui/imgui_internal.h"

enum class PlayerState {
    STARTTURN,
    CHOOSINGABILITY,
    CHOOSINGTARGET,
    ACTING,
    ENDTURN
};

class Artefact;

class Character : public Entity
{
protected :
    PlayerState currentState;

    std::shared_ptr<Artefact> artefact;

    float XPNeededForLvl2;
    float currentXP;
    float XPNeeded;

    float finalHP;
    float finalAD;
    float finalAP;
    float finalArmor;
    float finalPR;
    float finalXPNeeded;

    int abilitySelected;

    void levelUp();
    bool manageXP();

public:
    Character();
    void endRun();

    void addCurrentXP(float newXP);

    float getCurrentXP() const;
    float getXPNeeded() const;

    bool getArtefactAlreadyUsed();
    void setArtefactAlreadyUsed(bool value);

    void takeDamageEvent(Entity& target);

    std::shared_ptr<Artefact> getArtefact() const;
    void setArtefact(std::shared_ptr<Artefact> newArtefact);
};
