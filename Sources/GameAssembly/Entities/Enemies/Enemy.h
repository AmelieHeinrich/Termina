#pragma once
#include "../Entity.h"
#include "../../Artefacts/Artefact.h"
#pragma once

#pragma once

// Common
#include "../../Artefacts/Common/SmokeBomb.h"
#include "../../Artefacts/Common/BearSFoot.h"
#include "../../Artefacts/Common/KnightsBadge.h"
#include "../../Artefacts/Common/EelsEye.h"
//#include "../../Artefacts/Common/AbandonedTail.h"
#include "../../Artefacts/Common/ToeBone.h"
#include "../../Artefacts/Common/WolfFur.h"
#include "../../Artefacts/Common/Tail.h"

// Rare
//#include "../../Artefacts/Rare/ChaoticArmor.h"
//#include "../../Artefacts/Rare/KnightsHelmet.h"
//#include "../../Artefacts/Rare/Scale.h"
//#include "../../Artefacts/Rare/Feather.h"
//#include "../../Artefacts/Rare/BurningBone.h"
#include "../../Artefacts/Rare/RatTooth.h"
#include "../../Artefacts/Rare/WolfTooth.h"

// Epic
#include "../../Artefacts/Epic/MaliciousEye.h"
#include "../../Artefacts/Epic/BearsSalmon.h"
#include "../../Artefacts/Epic/CursedShield.h"
#include "../../Artefacts/Epic/CaspersEncyclopedia.h"
//#include "../../Artefacts/Epic/MermaidTail.h"
//#include "../../Artefacts/Epic/RattataSkull.h"
//#include "../../Artefacts/Epic/PackAura.h"

// Legendary
//#include "../../Artefacts/Legendary/ChaosScepter.h"
#include "../../Artefacts/Legendary/GreatBearMedal.h"
//#include "../../Artefacts/Legendary/DarkSword.h"
//#include "../../Artefacts/Legendary/Ectoplasm.h"
//#include "../../Artefacts/Legendary/Seaweed.h"
//#include "../../Artefacts/Legendary/RatEyeTalisman.h"
//#include "../../Artefacts/Legendary/ScaleOfTheWhale.h"
//#include "../../Artefacts/Legendary/EternalFlame.h"
//#include "../../Artefacts/Legendary/ForestRunes.h"
//#include "../../Artefacts/Legendary/Humerus.h"
//#include "../../Artefacts/Legendary/AlphaMedal.h"

// Unique
//#include "../../Artefacts/Unique/GargoyleSkull.h"

enum class Biome {
    FOREST,
    GRAVEYARD,
    OCEAN
};

enum class EnemyState
{
    STARTTURN,
    ACTING,
    ENDTURN
};

class Enemy : public Entity
{
protected:

    float baseExpDrop;
    float currentExpDrop;
    float maxExpDrop;

    float finalArmor;
    float finalPR;

    int landing;

    Biome biome;

    EnemyState enemyState;

public:
    Enemy();
    virtual std::shared_ptr<Artefact> createDrop();

    float getCurrentExpDrop() const;
};
