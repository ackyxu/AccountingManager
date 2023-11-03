#ifndef ACCOUNTCREATOR_H
#define ACCOUNTCREATOR_H

#include <Accounts.h>
#include <AccountType.h>

class AccountCreator{

    public:
        Accounts* CreateAccount(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active, bool groupHeader = false);
};

#endif