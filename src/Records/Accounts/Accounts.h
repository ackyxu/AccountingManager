#pragma once
#include <string>
using std::string;

class Accounts {
    private:
        int accNum;
        string accName;
        string accDesc;
        string accType;
        float accAmt = 0;
    
    public:
        Accounts(int accNum, string accName, string accDesc, string accType);
        string getAccNum();
        string getAccName();
        string getAccDesc();

};