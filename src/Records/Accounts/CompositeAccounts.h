#pragma once

#include <vector>
#include <Accounts.h>
#include <queue>



class CompositeAccounts: public Accounts {

    private:
        bool accountNumCompare(Accounts* acc1, Accounts* acc2);
        std::vector<Accounts*> subAccounts;

    public:
        CompositeAccounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int grpNUM, bool active, bool groupHeader);
        void addSubAccounts(Accounts* acc) override;
        bool CheckGroupContains(int subNumber) override;
        


};


