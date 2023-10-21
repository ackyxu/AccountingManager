#pragma once

#include <string>
#include <Accounts.h>
using std::string;

class Expenses : public Accounts {

    public:
        Expenses(int accNum, string accName, string accDesc);

};