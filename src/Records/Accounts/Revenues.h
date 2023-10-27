#pragma once

#include <string>
#include <Accounts.h>
using std::string;

class Revenues : public Accounts {

    public:
        Revenues(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active);

};