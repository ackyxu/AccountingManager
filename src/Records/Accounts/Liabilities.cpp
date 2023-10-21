#include <Liabilities.h>
#include <AccountType.h>

Liabilities::Liabilities(int accNum, string accName, string accDesc) : 
    Accounts(accNum, accName, accDesc, LIABILITY){

}