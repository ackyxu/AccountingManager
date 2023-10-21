#include <Accounts.h>

Accounts::Accounts(int accNum, string accName, string accDesc, AccountType accType) {
    this->accNum = accNum;
    this->accName = accName;
    this->accDesc = accDesc;
    this->accType = accType;
}

int Accounts::getAccNum(){
    return accNum;
}

string Accounts::getAccName(){
    return accName;
};
string Accounts::getAccDesc(){
    return accDesc;
};

AccountType Accounts::getAccType(){
    return accType;
}