#include <Revenues.h>
#include <AccountType.h>

Revenues::Revenues(int accNum, string accName, string accDesc, AccountType accType, bool group, int groupNUM, bool active): 
    Accounts(accNum, accName, accDesc, accType, group, groupNUM, active){
}