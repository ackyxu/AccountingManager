#include <Liabilities.h>
#include <AccountType.h>

Liabilities::Liabilities(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active, bool groupHeader): 
    Accounts(accNum, accName, accDesc, accType, group, groupNUM, active, groupHeader){

}