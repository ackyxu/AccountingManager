#include <Accounts.h>

Accounts::Accounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int grpNUM, bool active, bool groupHeader) {
    this->accNum = accNum;
    this->accName = accName;
    this->accDesc = accDesc;
    this->accType = accType;
    this->group = group;
    this->groupNum = grpNUM;
    this->active = active;
    this->groupHeader = groupHeader;
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



bool Accounts::getGroup(){
    return group;
}


int Accounts::getGroupNUM(){
    return groupNum;
}

bool Accounts::getActiveStatus(){
    return active;
}


