#include <Equities.h>
#include <AccountType.h>

Equities::Equities(int accNum, string accName, string accDesc) : 
    Accounts(accNum, accName, accDesc, EQUITY){
}