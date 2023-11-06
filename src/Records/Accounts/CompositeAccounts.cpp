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


std::vector<int> CompositeAccounts::ListSubAccountNum(){
    std::vector<int> subAccNum;
    for(auto pair: subAccounts){
        subAccNum.push_back(pair.first);
    }
    return subAccNum;
}

std::vector<int> CompositeAccounts::ListHeaderSubAccountNum(){

    std::vector<int> subAccNum;
    for(auto pair: subAccounts){
        if((pair.second)->getHeaderFlag()) subAccNum.push_back(pair.first);
    }
    return subAccNum;

}

