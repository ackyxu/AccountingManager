#pragma once
#include <string>
#include <AccountType.h>
using std::string;

class Accounts {
    private:
        int accNum;
        string accName;
        string accDesc;
        AccountType accType;
        float accAmt = 0;
    
    public:
        Accounts(int accNum, string accName, string accDesc, AccountType accType);
        int getAccNum();
        string getAccName();
        string getAccDesc();
        AccountType getAccType();

};