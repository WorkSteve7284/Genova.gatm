#pragma once
#include "Variables.h"
#include "Tools.h"

class Genova {
public:
    void start();
private:
    Variables variables;
    Tools tools{variables};
};
