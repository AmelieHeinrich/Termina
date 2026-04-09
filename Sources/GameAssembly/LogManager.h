#pragma once
#include <vector>
#include <string>
#include "../ThirdParty/ImGui/imgui.h"

struct LogEntry
{
    std::string message;
    ImVec4 color;

    LogEntry(const std::string& msg, ImVec4 col = ImVec4(1,1,1,1))
        : message(msg), color(col) {}
};

class LogManager
{
    LogManager() = default;

    std::vector<LogEntry> logs;
    size_t maxLogs = 100;

public:
    static LogManager& getInstance();

    void addLog(const std::string& message, ImVec4 color = ImVec4(1,1,1,1));
    void drawImGui();
    void addSeparator(ImVec4 color = ImVec4(1,1,1,1));
};