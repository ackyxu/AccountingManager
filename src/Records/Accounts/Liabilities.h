#pragma once

#include <string>
#include <Accounts.h>
using std::string;

class Liabilities : public Accounts {

    public:
        Liabilities(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active);

};