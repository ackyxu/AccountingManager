#include <CompositeAccounts.h>


CompositeAccounts::CompositeAccounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active, bool groupHeader):
    Accounts(accNum, accName, accDesc, accType, group, groupNUM, active, groupHeader) {
    }
    
void CompositeAccounts::addSubAccounts(Accounts* acc){
    subAccounts.push_back(acc);
}

bool CompositeAccounts::CheckGroupContains(int subNumber){
    for(Accounts* acc: subAccounts){
        if (acc->getAccNum() == subNumber) return true;
    }
    return false;
}

