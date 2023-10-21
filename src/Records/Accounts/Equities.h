#pragma once

#include <string>
#include <Accounts.h>
using std::string;

class Equities : public Accounts {

    public:
        Equities(int accNum, string accName, string accDesc);

};