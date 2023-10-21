#include <Revenues.h>
#include <AccountType.h>

Revenues::Revenues(int accNum, string accName, string accDesc) : 
    Accounts(accNum, accName, accDesc, REVENUE){
}