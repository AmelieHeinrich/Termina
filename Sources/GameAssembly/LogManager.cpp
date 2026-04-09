#include "LogManager.h"
#include "../ThirdParty/ImGui/imgui.h"
#include <sstream>

LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

void LogManager::addLog(const std::string& message, ImVec4 color)
{
    logs.emplace_back(message, color);

    if (logs.size() > maxLogs)
        logs.erase(logs.begin());
}

void LogManager::addSeparator(ImVec4 color)
{
    logs.emplace_back("__SEPARATOR__", color);

    if (logs.size() > maxLogs)
        logs.erase(logs.begin());
}

void LogManager::drawImGui()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec4 BgColor = ImVec4(0.200f, 0.133f, 0.075f, 1.0f);
    ImVec4 ItemsColor = ImVec4(0.349f, 0.251f, 0.169f, 1.0f);

    float logsWindowWidth = viewport->Size.x / 4.0f;

    ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - logsWindowWidth, 0));
    ImGui::SetNextWindowSize(ImVec2(logsWindowWidth, viewport->Size.y - viewport->Size.y * 1.0f / 3.0f - viewport->Size.y / 4.0f)); // viewport->Size.y / 4.0f pour les artefacts
    ImGui::PushStyleColor(ImGuiCol_WindowBg, BgColor);
    ImGui::Begin("Fight Log", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::BeginChild(
        "ScrollingRegion",
        ImVec2(0, 0),
        true,
        ImGuiWindowFlags_HorizontalScrollbar
    );

    size_t start = logs.size() > 20 ? logs.size() - 20 : 0;

    for (size_t i = start; i < logs.size(); i++)
    {
        if (logs[i].message == "__SEPARATOR__")
            ImGui::Separator();
        else
            ImGui::TextColored(logs[i].color, "%s", logs[i].message.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
    ImGui::PopStyleColor();
}