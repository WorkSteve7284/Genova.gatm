#pragma once
#include <string>
#include <map>
#include <functional>
#include <variant>
#include <iostream>
#include <sstream>
#include <random>
#include "Variables.h"

class Tools {
public:
    using ToolFunc = std::function<void(const std::string& input)>;

    Tools(Variables& vars);
    void handle(const std::string& input);

private:
    Variables& variables;
    std::map<std::string, ToolFunc> toolMap;

    void toolHelp(const std::string& input);
    void toolCalc(const std::string& input);
    void toolConvert(const std::string& input);
    void toolSet(const std::string& input);
    void toolGet(const std::string& input);
    void toolRand(const std::string& input);
    void toolTime(const std::string& input);
};
