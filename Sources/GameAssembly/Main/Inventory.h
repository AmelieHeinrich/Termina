#pragma once

#include <string>
#include <unordered_map>
#include "../Artefacts/Artefact.h"
#include "../Entities/Characters/Character.h"

enum class EInventoryState {
    SHOWALL,
    SHOWONE,
    ASSIGNONE
};


class Inventory {
    std::unordered_map<std::string, int> items;
    std::vector<std::shared_ptr<Artefact>> artefactsInventory;
    std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>> mapCharacterToArtefact;
    EInventoryState currentInventoryState;

    std::shared_ptr<Artefact> targetArtefact;
    std::shared_ptr<Character> selectedCharacter;

public:
    Inventory();
    void addItem(const std::string& name, int amount);
    int getItemCount(const std::string& name) const;
    void removeItem(const std::string& name, int amount);
    void checkArtefactsInventory();

    void addArtefact(std::shared_ptr<Artefact> artefact);
    std::vector<std::shared_ptr<Artefact>> getArtefactsInventory() const;
    void removeArtefactInventory(std::shared_ptr<Artefact> artefact);

    void drawArtefactsInventory(std::vector<std::shared_ptr<Entity>>& characters);

    void setMapCharacterToArtefact(const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>>& newMap);
    const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>>& getMapCharacterToArtefact() const;
};