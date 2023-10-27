#include <AccountCreator.h>
#include <Assets.h>
#include <Liabilities.h>
#include <Equities.h>
#include <Revenues.h>
#include <Expenses.h>

Accounts* AccountCreator::CreateAccount(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active){
    

    if(accType == ASSET){
        return new Assets(accNum, accName,accDesc,accType,group, groupNUM, active);
    }
    else if(accType == LIABILITY) {
        return new Liabilities(accNum, accName,accDesc,accType, group, groupNUM, active);
    }
    else if(accType == EQUITY) {
        return new Equities(accNum, accName,accDesc, accType,group, groupNUM, active);   
    }
    else if(accType == REVENUE) {
        return new Revenues(accNum, accName,accDesc,accType, group, groupNUM, active);
    }
    else{    // accType == EXPENSE
         return new Expenses(accNum, accName,accDesc,accType, group, groupNUM, active);
    }

    
}