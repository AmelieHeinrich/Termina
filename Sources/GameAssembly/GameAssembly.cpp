#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>
#include <ImGui/imgui.h>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"

#include "Main/Game.h"
#include "Entities/Characters/Tank/Diane.h"
#include "Entities/Characters/Close DPS/Alex.h"
#include "Entities/Characters/Support/Marcus.h"
#include "Entities/Characters/Range DPS/Edward.h"
#include "Entities/Characters/Close DPS/Penelope.h"
#include "Entities/Characters/Support/Claire.h"
#include "Entities/Characters/Range DPS/Brutus.h"
#include "Entities/Characters/Tank/Emilie.h"

#include "Entities/Enemies/Forest/Rat.h"
#include "Entities/Enemies/Forest/Wolf.h"
#include "Entities/Enemies/Forest/Bear.h"
#include "Entities/Enemies/Forest/Hawk.h"
#include "Entities/Enemies/Graveyard/Ghost.h"
#include "Entities/Enemies/Graveyard/AdeptOfTheChaos.h"
#include "Entities/Enemies/Graveyard/DarkKnight.h"
#include "Entities/Enemies/Graveyard/Skeleton.h"
#include "Entities/Enemies/Ocean/Kelpie.h"
#include "Entities/Enemies/Ocean/Dunkleosteus.h"
#include "Entities/Enemies/Ocean/Mermaid.h"
#include "Entities/Enemies/Ocean/Eel.h"

#include "Entities/Enemies/Forest/RunicDeer.h"
#include "Entities/Enemies/Forest/RedDragon.h"
#include "Entities/Enemies/Graveyard/Gargoyle.h"
#include "Entities/Enemies/Ocean/Whale.h"

COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")
    REGISTER_COMPONENT(Game, "Game")
    //Characters
    REGISTER_COMPONENT(Diane, "Diane")
    REGISTER_COMPONENT(Alex, "Alex")
    REGISTER_COMPONENT(Marcus, "Marcus")
    REGISTER_COMPONENT(Edward, "Edward")
    REGISTER_COMPONENT(Penelope, "Penelope")
    REGISTER_COMPONENT(Claire, "Claire")
    REGISTER_COMPONENT(Brutus, "Brutus")
    REGISTER_COMPONENT(Emilie, "Emilie")

    //Enemies
    REGISTER_COMPONENT(Rat, "Rat")
    REGISTER_COMPONENT(Wolf, "Wolf")
    REGISTER_COMPONENT(Bear, "Bear")
    REGISTER_COMPONENT(Hawk, "Hawk")
    REGISTER_COMPONENT(Ghost, "Ghost")
    REGISTER_COMPONENT(AdeptOfTheChaos, "AdeptOfTheChaos")
    REGISTER_COMPONENT(DarkKnight, "DarkKnight")
    REGISTER_COMPONENT(Skeleton, "Skeleton")
    REGISTER_COMPONENT(Kelpie, "Kelpie")
    REGISTER_COMPONENT(Dunkleosteus, "Dunkleosteus")
    REGISTER_COMPONENT(Mermaid, "Mermaid")
    REGISTER_COMPONENT(Eel, "Eel")

    //Boss
    REGISTER_COMPONENT(RunicDeer, "RunicDeer")
    REGISTER_COMPONENT(RedDragon, "RedDragon")
    REGISTER_COMPONENT(Gargoyle, "Gargoyle")
    REGISTER_COMPONENT(Whale, "Whale")


COMPONENT_MODULE_END()

TERMINA_DLL_EXPORT void SetImGuiContext(void* ctx, void* allocFunc, void* freeFunc, void* userData)
{
    ImGui::SetCurrentContext(static_cast<ImGuiContext*>(ctx));
    ImGui::SetAllocatorFunctions(
        reinterpret_cast<ImGuiMemAllocFunc>(allocFunc),
        reinterpret_cast<ImGuiMemFreeFunc>(freeFunc),
        userData);
}
