#include "Tools.h"
#include <chrono>
#include <iomanip>

Tools::Tools(Variables& vars) : variables(vars) {
    toolMap["help"] = [this](auto&& input){ toolHelp(input); };
    toolMap["calc"] = [this](auto&& input){ toolCalc(input); };
    toolMap["convert"] = [this](auto&& input){ toolConvert(input); };
    toolMap["set"] = [this](auto&& input){ toolSet(input); };
    toolMap["get"] = [this](auto&& input){ toolGet(input); };
    toolMap["rand"] = [this](auto&& input){ toolRand(input); };
    toolMap["time"] = [this](auto&& input){ toolTime(input); };
}

void Tools::handle(const std::string& input){
    if(input.empty()) return;
    std::stringstream ss(input);
    std::string cmd;
    ss >> cmd;

    if(toolMap.count(cmd)){
        toolMap[cmd](input);
    } else {
        std::cout << "Unknown command: '" << cmd << "'. Type 'help'.\n";
    }
}

void Tools::toolHelp(const std::string&){
    std::cout << "Available commands:\n";
    for(auto& [k,_]: toolMap) std::cout << "  " << k << "\n";
    std::cout << "  exit\n";
}

void Tools::toolCalc(const std::string& input){
    std::stringstream ss(input.substr(5));
    double a,b; char op;
    ss >> a >> op >> b;
    double res;
    switch(op){
        case '+': res=a+b; break;
        case '-': res=a-b; break;
        case '*': res=a*b; break;
        case '/': res=(b!=0)?a/b:NAN; break;
        default: std::cout << "Unsupported operator.\n"; return;
    }
    std::cout << "Result: " << res << "\n";
}

void Tools::toolConvert(const std::string& input){
    std::stringstream ss(input);
    std::string cmd, fromUnit, toUnit, tmp; double value;
    ss >> cmd >> value >> fromUnit >> tmp >> toUnit;
    std::map<std::string,double> toMeters = {
        {"km",1000},{"m",1},{"cm",0.01},{"mm",0.001},
        {"mi",1609.34},{"ft",0.3048},{"in",0.0254}
    };
    if(toMeters.count(fromUnit) && toMeters.count(toUnit)){
        double result = value*toMeters[fromUnit]/toMeters[toUnit];
        std::cout << value << " " << fromUnit << " = " << result << " " << toUnit << "\n";
    } else std::cout << "Unsupported units.\n";
}

void Tools::toolSet(const std::string& input){
    std::stringstream ss(input);
    std::string cmd, varName, valueStr;
    ss >> cmd >> varName;
    std::getline(ss, valueStr); if(!valueStr.empty() && valueStr[0]==' ') valueStr.erase(0,1);
    if(varName.empty() || valueStr.empty()){ std::cout<<"Usage: set <var> <value>\n"; return;}
    variables.set(varName,valueStr);
}

void Tools::toolGet(const std::string& input){
    std::stringstream ss(input);
    std::string cmd, varName; ss >> cmd >> varName;
    if(varName.empty()){ std::cout<<"Usage: get <var>\n"; return;}
    std::cout << varName << " = " << variables.toString(varName) << "\n";
}

void Tools::toolRand(const std::string& input){
    std::stringstream ss(input); std::string cmd; int min=0, max=100;
    ss >> cmd >> min >> max;
    if(min>max) std::swap(min,max);
    int r = std::rand()%(max-min+1)+min;
    std::cout << "Random: " << r << "\n";
}

void Tools::toolTime(const std::string&){
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time: " << std::put_time(std::localtime(&t), "%F %T") << "\n";
}
