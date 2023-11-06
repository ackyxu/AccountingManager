#pragma once

#include <unordered_map>
#include <Accounts.h>
#include <queue>
using std::unordered_map;



class CompositeAccounts: public Accounts {

    private:
        bool accountNumCompare(Accounts* acc1, Accounts* acc2);
        unordered_map <int,Accounts*> subAccounts;

    public:
        CompositeAccounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int grpNUM, bool active, bool groupHeader);
        void addSubAccounts(Accounts* acc) override;
        int removeSubAccounts(int accNum) override;
        bool CheckGroupContains(int subNumber) override;
        bool CanDelete() override;
        // vector<int> ListSubAccountNum();
        


};


