#include "Variables.h"
#include <regex>
#include <string>
#include <sstream>

void Variables::set(const std::string& name, const std::string& valueStr) {
    try {
        size_t pos;
        int intVal = std::stoi(valueStr, &pos);
        if(pos == valueStr.size()){ variables[name] = intVal; return; }
    } catch(...) {}
    try {
        size_t pos;
        double doubleVal = std::stod(valueStr, &pos);
        if(pos == valueStr.size()){ variables[name] = doubleVal; return; }
    } catch(...) {}
    variables[name] = valueStr;
}

Variables::VarValue Variables::get(const std::string& name){
    return variables.count(name) ? variables[name] : std::string("");
}

std::string Variables::toString(const std::string& name){
    if(!variables.count(name)) return "";
    VarValue& val = variables[name];
    if(std::holds_alternative<int>(val)) return std::to_string(std::get<int>(val));
    if(std::holds_alternative<double>(val)) return std::to_string(std::get<double>(val));
    return std::get<std::string>(val);
}

std::string Variables::substitute(const std::string& input){
    std::string result = input;
    std::regex varRegex(R"(\$([a-zA-Z_][a-zA-Z0-9_]*))");
    std::smatch match;
    std::string::const_iterator searchStart(result.cbegin());

    while(std::regex_search(searchStart, result.cend(), match, varRegex)){
        std::string varName = match[1].str();
        std::string valueStr = toString(varName);
        result.replace(match.position(0), match.length(0), valueStr);
        searchStart = result.cbegin() + match.position(0) + valueStr.length();
    }
    return result;
}
