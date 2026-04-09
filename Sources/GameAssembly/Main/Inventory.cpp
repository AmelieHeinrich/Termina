#include "Inventory.h"

Inventory::Inventory() {
    currentInventoryState = EInventoryState::SHOWALL;
}

void Inventory::addItem(const std::string& name, int amount) {
    if (amount <= 0) return;
    items[name] += amount;
}

int Inventory::getItemCount(const std::string& name) const {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;
    }
    return 0;
}

void Inventory::removeItem(const std::string& name, int amount) {
    if (amount <= 0) return;

    auto it = items.find(name);
    if (it != items.end()) {
        it->second -= amount;

        if (it->second <= 0) {
            items.erase(it);
        }
    }
}

void Inventory::addArtefact(std::shared_ptr<Artefact> artefact)
{
    if (!artefact) return;

    artefactsInventory.push_back(artefact);
}

std::vector<std::shared_ptr<Artefact>> Inventory::getArtefactsInventory() const
{
    return artefactsInventory;
}

void Inventory::removeArtefactInventory(std::shared_ptr<Artefact> artefact)
{
    std::erase(artefactsInventory, artefact);
}

void Inventory::checkArtefactsInventory() {
    for (size_t i = 0; i < artefactsInventory.size(); ++i) {
        for (size_t j = i + 1; j < artefactsInventory.size();) {

            if (artefactsInventory[i]->getName() == artefactsInventory[j]->getName()) {

                int newLevel = artefactsInventory[i]->getLevel() + artefactsInventory[j]->getLevel();
                artefactsInventory[i]->setLevel(std::min(newLevel, 5));

                artefactsInventory.erase(artefactsInventory.begin() + j);
            } else {
                ++j;
            }
        }
    }
}

void Inventory::drawArtefactsInventory(std::vector<std::shared_ptr<Entity>>& characters) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec4 BgColor = ImVec4(0.200f, 0.133f, 0.075f, 1.0f);
    ImVec4 ItemsColor = ImVec4(0.349f, 0.251f, 0.169f, 1.0f);

    float logsWindowWidth = viewport->Size.x / 4.0f;

    switch (currentInventoryState) {
        case EInventoryState::SHOWALL : {
            ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - logsWindowWidth, viewport->Size.y - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y / 4.0f));
            ImGui::SetNextWindowSize(ImVec2(logsWindowWidth, viewport->Size.y / 4.0f)); // viewport->Size.y / 4.0f pour les artefacts
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Artefact Inventory",nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            if (!artefactsInventory.empty()) {
                for (int i = 0; i < artefactsInventory.size(); i++)
                {
                    std::string label = artefactsInventory[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        targetArtefact = artefactsInventory[i];
                        currentInventoryState = EInventoryState::SHOWONE;
                    }
                }
            }
            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }

        case EInventoryState::SHOWONE : {
            ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - logsWindowWidth, viewport->Size.y - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y / 4.0f));
            ImGui::SetNextWindowSize(ImVec2(logsWindowWidth, viewport->Size.y / 4.0f)); // viewport->Size.y / 4.0f pour les artefacts
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Artefact Info",nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::Text("Name : %s", targetArtefact->getName().c_str());
            ImGui::Text("Description : %s", targetArtefact->getDescription().c_str());

            if (ImGui::Button("Assign")) {
                currentInventoryState = EInventoryState::ASSIGNONE;
            }
            if (ImGui::Button("Return")) {
                currentInventoryState = EInventoryState::SHOWALL;
            }

            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }

        case EInventoryState::ASSIGNONE : {
            ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - logsWindowWidth, viewport->Size.y - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y / 4.0f));
            ImGui::SetNextWindowSize(ImVec2(logsWindowWidth, viewport->Size.y / 4.0f)); // viewport->Size.y / 4.0f pour les artefacts
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Assign Artefact",nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            for (int i = 0; i < characters.size(); i++)
            {
                std::string label = characters[i]->getName() + "##" + std::to_string(i);

                if (ImGui::Button(label.c_str())) {
                    selectedCharacter = std::static_pointer_cast<Character>(characters[i]);
                    selectedCharacter->setArtefact(targetArtefact);
                    currentInventoryState = EInventoryState::SHOWALL;
                }
            }
            if (ImGui::Button("Return")) {
                currentInventoryState = EInventoryState::SHOWONE;
            }

            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }
    }
}

const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact> > &Inventory::getMapCharacterToArtefact() const {
    return mapCharacterToArtefact;
}

void Inventory::setMapCharacterToArtefact(const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>>& newMap) {
    mapCharacterToArtefact = newMap;
}
