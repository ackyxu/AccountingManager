#pragma once

#include <string>
#include <Accounts.h>
using std::string;

class Assets : public Accounts {

    public:
        Assets(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active, bool groupHeader);

};