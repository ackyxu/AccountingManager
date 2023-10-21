#include <Expenses.h>
#include <AccountType.h>

Expenses::Expenses(int accNum, string accName, string accDesc) : 
    Accounts(accNum, accName, accDesc, EXPENSE){
}