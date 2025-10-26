#pragma once
#include <string>
#include <map>
#include <variant>

class Variables {
public:
    using VarValue = std::variant<int, double, std::string>;

    void set(const std::string& name, const std::string& valueStr);
    VarValue get(const std::string& name);
    std::string toString(const std::string& name);
    std::string substitute(const std::string& input);

private:
    std::map<std::string, VarValue> variables;
};
