
#include "PlayerXP.h"

#include <cmath>

#include "../../ThirdParty/ImGui/imgui.h"

PlayerXP::PlayerXP() {
    upgradeState = EUpgradeState::CHECKINGXP;
    choosing = false;

    XPNeededForLvl2 = 100;
    finalXPNeeded = 100000;
    currentXP = 0;
    XPNeeded = XPNeededForLvl2;
}

Bonus PlayerXP::generateBonus(int rarity)
{
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, 7);
    int typeIndex = dist(rng);

    EBonusType type = static_cast<EBonusType>(typeIndex);
    const auto& values = rarityTable[rarity];

    float value;

    switch (type) {
        case EBonusType::HEALALL: value = values.healAll; break;
        case EBonusType::HEALSINGLE: value = values.healSingle; break;
        case EBonusType::AP: value = values.ap; break;
        case EBonusType::AD: value = values.ad; break;
        case EBonusType::ARMOR: value = values.armor; break;
        case EBonusType::MAGICRESIST: value = values.mr; break;
        case EBonusType::CLASSSTATS: value = values.classStats; break;
        case EBonusType::UPGRADECHANCE: value = values.upgradeChance; break;
        default: value = 0; break;
    }

    return { type, EClass::TANK, nullptr, value, rarity };
}

std::string PlayerXP::getBonusText(const Bonus& bonus) {
    switch (bonus.type) {
        case EBonusType::HEALALL:
            return "Heal " + std::to_string((int)std::round(bonus.value)) + "% of Max HP of everyone";

        case EBonusType::HEALSINGLE:
            return "Heal " + std::to_string((int)std::round(bonus.value)) + "% of Max HP to one character";

        case EBonusType::AP:
            return "AP +" + std::to_string((int)std::round(bonus.value)) + "% to one character";

        case EBonusType::AD:
            return "AD +" + std::to_string((int)std::round(bonus.value)) + "% to one character";

        case EBonusType::ARMOR:
            return "Armor +" + std::to_string((int)std::round(bonus.value)) + "% to one character";

        case EBonusType::MAGICRESIST:
            return "Magic Resist +" + std::to_string((int)std::round(bonus.value)) + "% to one character";

        case EBonusType::CLASSSTATS:
            return "ClassStats +" + std::to_string((int)std::round(bonus.value)) + "% for one Class";

        case EBonusType::UPGRADECHANCE:
            return "+" + std::to_string((int)std::round(bonus.value)) + "% better upgrades next level";

        default:
            return "Unknown bonus";
    }
}

void PlayerXP::startRun() {
    bonusesToApply.clear();
}

bool PlayerXP::levelUp(int level)
{
    if (currentXP >= XPNeeded)
    {
        currentXP -= XPNeeded;
        XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (9999 - 1));
        return true;
    }
    return false;
}

bool PlayerXP::upgradeSystem(int level, std::vector<std::shared_ptr<Entity>> characters)
{
    static std::mt19937 rng2(rd());

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec4 BgColor = ImVec4(0.200f, 0.133f, 0.075f, 1.0f);

    ImVec4 normalColor  = ImVec4(0.231f, 0.153f, 0.086f, 1.0f);
    ImVec4 hoverColor   = ImVec4(0.212f, 0.133f, 0.071f, 1.0f);
    ImVec4 activeColor  = ImVec4(0.161f, 0.094f, 0.043f, 1.0f);

    switch (upgradeState) {
        case EUpgradeState::CHECKINGXP : {
            if (!levelUp(level))
            {
                return true;
            }
            upgradeState = EUpgradeState::GENERATEUPGRADE;
            return false;
        }

        case EUpgradeState::GENERATEUPGRADE : {
            bonusChoices.clear();

            std::uniform_int_distribution<int> rarity(1, range);

            for (int i = 0; i < 3; i++)
            {
                int rarityPercent = rarity(rng2);

                if (rarityPercent <= 5) { bonusChoices.push_back(generateBonus(4)); }
                else if (rarityPercent <= 15) { bonusChoices.push_back(generateBonus(3)); }
                else if (rarityPercent <= 30) { bonusChoices.push_back(generateBonus(2)); }
                else if (rarityPercent <= 100) { bonusChoices.push_back(generateBonus(1)); }
            }
            range = 100;
            upgradeState = EUpgradeState::CHOOSINGUPGRADE;
            return false;
        }

        case EUpgradeState::CHOOSINGUPGRADE : {

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Choose an upgrade", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::Columns(3, nullptr, true);

            ImGui::SetWindowFontScale(3.f);

            for (int i = 0; i < bonusChoices.size(); i++) {
                auto& choice = bonusChoices[i];
                std::string label = "Choice" + std::to_string(i + 1);
                ImGui::BeginChild(label.c_str(), ImVec2(0, -1), true);

                ImGui::Dummy(ImVec2(0, 250));


                if (choice.rarity == 1) color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
                else if (choice.rarity == 2) color = ImVec4(0.2f, 0.4f, 1.0f, 1.0f);
                else if (choice.rarity == 3) color = ImVec4(0.8f, 0.6f, 1.0f, 1.0f);
                else if (choice.rarity == 4) color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
                else color = ImVec4(1.0f,1.0f,1.0f,1.0f);

                float textWidthRarity = ImGui::CalcTextSize(getRarityString(choice.rarity).c_str()).x;
                float availRarity = ImGui::GetContentRegionAvail().x;
                ImGui::SetCursorPosX((availRarity - textWidthRarity) * 0.5f);
                ImGui::SetWindowFontScale(2.f);
                ImGui::TextColored(color, "%s", getRarityString(choice.rarity).c_str());

                ImGui::Separator();

                float textWidth = ImGui::CalcTextSize(getBonusText(choice).c_str()).x;
                float avail = ImGui::GetContentRegionAvail().x;
                ImGui::SetCursorPosX((avail - textWidth) * 0.5f);
                ImGui::SetWindowFontScale(2.f);
                ImGui::TextColored(color, "%s", getBonusText(choice).c_str());

                ImGui::Dummy(ImVec2(0, 200));

                float buttonWidth = viewport->Size.x / 6.0f;
                ImGui::SetCursorPosX((avail - buttonWidth) * 0.5f);
                ImGui::SetCursorPosY(viewport->Size.y * 4.0f / 5.0f);

                std::string labelB = "Choose##" + std::to_string(i);

                {
                    ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
                    if (ImGui::Button(labelB.c_str(), ImVec2(buttonWidth, 0))) {
                        bonusesToApply.push_back(std::make_unique<Bonus>(choice));
                        if (bonusesToApply.back()->type == EBonusType::CLASSSTATS) {
                            upgradeState = EUpgradeState::SELECTCLASS;
                        }
                        else if (bonusesToApply.back()->type == EBonusType::UPGRADECHANCE) {
                            range -= bonusesToApply.back()->value;
                            bonusesToApply.pop_back(); //to not keep unusefull bonus for applyBonuses()
                            upgradeState = EUpgradeState::CHECKINGXP;
                        }
                        else if (bonusesToApply.back()->type != EBonusType::HEALALL) {
                            upgradeState = EUpgradeState::SELECTTARGET;
                        }
                        else
                            upgradeState = EUpgradeState::CHECKINGXP;
                    }
                    ImGui::PopStyleColor(3);
                }

                ImGui::EndChild();

                if ((i + 1) % 3 != 0)
                    ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::End();
            ImGui::PopStyleColor();
            return false;
        }

        case EUpgradeState::SELECTTARGET : {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Choose target", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

            ImGui::SetWindowFontScale(5.f);

            for (int i = 0; i < characters.size(); i++)
            {
                std::string label = characters[i]->getName() + "##" + std::to_string(i);

                float textWidth = ImGui::CalcTextSize(label.c_str()).x;
                float avail = ImGui::GetContentRegionAvail().x;
                ImGui::SetCursorPosX((avail - textWidth) * 0.5f);

                ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
                if (ImGui::Button(label.c_str())) {
                    bonusesToApply.back()->character = characters[i];
                    upgradeState = EUpgradeState::CHECKINGXP;
                }
                ImGui::PopStyleColor(3);
                ImGui::Separator();
            }
            ImGui::End();
            ImGui::PopStyleColor();

            return false;
        }

        case EUpgradeState::SELECTCLASS : {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(viewport->Size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
            ImGui::Begin("Choose Class", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

            ImGui::SetWindowFontScale(5.f);

            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("CloseDPS")) {
                bonusesToApply.back()->bonusClass = EClass::CLOSEDDPS;
                upgradeState = EUpgradeState::CHECKINGXP;
            }
            ImGui::PopStyleColor(3);
            ImGui::Separator();
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("RangeDPS")) {
                bonusesToApply.back()->bonusClass = EClass::RANGEDDPS;
                upgradeState = EUpgradeState::CHECKINGXP;
            }
            ImGui::PopStyleColor(3);
            ImGui::Separator();
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("Tank")) {
                bonusesToApply.back()->bonusClass = EClass::TANK;
                upgradeState = EUpgradeState::CHECKINGXP;
            }
            ImGui::PopStyleColor(3);
            ImGui::Separator();
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
            if (ImGui::Button("Support")) {
                bonusesToApply.back()->bonusClass = EClass::SUPPORT;
                upgradeState = EUpgradeState::CHECKINGXP;
            }
            ImGui::PopStyleColor(3);
            ImGui::End();
            ImGui::PopStyleColor();

            return false;
        }

        default : return true;
    }
}

void PlayerXP::applyBonuses(std::vector<std::shared_ptr<Entity>> characters) {
    if (!bonusesToApply.empty())
    {
        for (auto& bonus : bonusesToApply) {
            EBonusType type = bonus->type;
            float value = bonus->value;

            switch (type) {
                case EBonusType::HEALALL:
                    for (auto& chara : characters) {
                        float healValue = chara->getMaxHealth() * value / 100;
                        chara->setCurrentHealth(chara->getCurrentHealth() + healValue);
                        if (chara->getCurrentHealth() > chara->getMaxHealth()) chara->setCurrentHealth(chara->getMaxHealth());
                    }
                    break;

                case EBonusType::HEALSINGLE: {
                    if (!bonus->character) break;
                    float healValue = bonus->character->getMaxHealth() * value / 100;
                    bonus->character->setCurrentHealth(bonus->character->getCurrentHealth() + healValue);
                    if (bonus->character->getCurrentHealth() > bonus->character->getMaxHealth()) bonus->character->setCurrentHealth(bonus->character->getMaxHealth());
                    break;
                }

                case EBonusType::AP: {
                    if (!bonus->character) break;
                    float APValue = bonus->character->getMaxAttackPower() * value / 100;
                    bonus->character->setCurrentAttackPower(bonus->character->getCurrentAttackPower() + APValue);
                    break;
                }

                case EBonusType::AD: {
                    if (!bonus->character) break;
                    float ADValue = bonus->character->getMaxAttackDamage() * value / 100;
                    bonus->character->setCurrentAttackDamage(bonus->character->getCurrentAttackDamage() + ADValue);
                    break;
                }

                case EBonusType::ARMOR:
                    if (!bonus->character) break;
                    bonus->character->setCurrentArmor(bonus->character->getCurrentArmor() + value);
                    break;

                case EBonusType::MAGICRESIST:
                    if (!bonus->character) break;
                    bonus->character->setCurrentPowerResist(bonus->character->getCurrentPowerResist() + value);
                    break;

                case EBonusType::CLASSSTATS:
                    for (auto& chara : characters) {
                        if (chara->getClass() == bonus->bonusClass) {

                            float APValue = chara->getMaxAttackPower() * value / 100;
                            chara->setCurrentAttackPower(chara->getCurrentAttackPower() + APValue);
                            float ADValue = chara->getMaxAttackDamage() * value / 100;
                            chara->setCurrentAttackDamage(chara->getCurrentAttackDamage() + ADValue);

                            chara->setCurrentArmor(chara->getCurrentArmor() + value);
                            chara->setCurrentPowerResist(chara->getCurrentPowerResist() + value);
                        }
                    }
                    break;

                case EBonusType::UPGRADECHANCE:
                    break;

                default: break;
            }
        }
    }
}

bool PlayerXP::getChoosing() const { return choosing; }

void PlayerXP::addCurrentXP(int xpToAdd) { currentXP += xpToAdd; }

std::string PlayerXP::getRarityString(int rarity) {
    switch (rarity) {
        case 1:
            return "Common";
        case 2:
            return "Rare";
        case 3:
            return "Epic";
        case 4:
            return "Legendary";
        default:
            return "Unknown";
            break;
    }
}
