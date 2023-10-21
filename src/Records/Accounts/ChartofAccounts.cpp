#include <ChartOfAccounts.h>
#include <iostream>

ChartOfAccounts::ChartOfAccounts(   pair<int,int> assetRange, pair<int,int> liabilityRange,
                                    pair<int,int> equityRange,pair<int,int> revenueRange,
                                    pair<int,int> expenseRange) {

        this->assetRange = assetRange;
        this->liabilityRange = liabilityRange;
        this->equityRange = equityRange;
        this->revenueRange = revenueRange;
        this->expenseRange = expenseRange;
    
}

int ChartOfAccounts::CreateAccount(int accNum, string accName, string accDesc, bool group){

    if (accNum >= assetRange.first && accNum <= assetRange.second ) {
        if(coa.find(accNum) == coa.end()) {
            coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, ASSET, group);
            return 0;
        }
        else return 1;
    }

    else if (accNum >= liabilityRange.first && accNum <= liabilityRange.second){
        if(coa.find(accNum) == coa.end()) {
            coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, LIABILITY, group);
            return 0;
        }
        else return 1;
    }

    else if (accNum >= equityRange.first && accNum <= equityRange.second){
        if(coa.find(accNum) == coa.end()) {
            coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, EQUITY, group);
            return 0;
        }
        else return 1;

    }

    else if (accNum >= revenueRange.first && accNum <= revenueRange.second){
        if(coa.find(accNum) == coa.end()) {
            coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, REVENUE, group);
            return 0;
        }
        else return 1;

    }
     
    else if (accNum >= expenseRange.first && accNum <= expenseRange.second){
        if(coa.find(accNum) == coa.end()) {
            coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, EXPENSE, group);
            return 0;
        }
        else return 1;
    } else return 2;

}


int ChartOfAccounts::getAccount(int accNum, Accounts** acc){
    if(coa.find(accNum) != coa.end()) {
        *acc = coa[accNum];
        return 0;
    } else {
        return 1;
    }

}

                            