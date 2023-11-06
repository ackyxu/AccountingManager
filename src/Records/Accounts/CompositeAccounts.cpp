#include <CompositeAccounts.h>


CompositeAccounts::CompositeAccounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active, bool groupHeader):
    Accounts(accNum, accName, accDesc, accType, group, groupNUM, active, groupHeader) {
    }
    
void CompositeAccounts::addSubAccounts(Accounts* acc){
    if (subAccounts.find(acc->getAccNum()) == subAccounts.end()){
        subAccounts[acc->getAccNum()] = acc;
    }
}

bool CompositeAccounts::CheckGroupContains(int subNumber){
    return subAccounts.find(subNumber) != subAccounts.end();
}

int CompositeAccounts::removeSubAccounts(int accNum){
    if (subAccounts.find(accNum) != subAccounts.end()){
        subAccounts.erase(accNum);
        return 0;
    } else return 2;

}

bool CompositeAccounts::CanDelete(){
    return subAccounts.empty();
}


// vector<int> CompositeAccounts::ListSubAccountNum(){
//     vector<int> subAccNum;
//     for(auto acc: subAccounts){
//         subAccounts.push_back(acc->getAccNum());

//     }
//     return subAccNum;
// }

