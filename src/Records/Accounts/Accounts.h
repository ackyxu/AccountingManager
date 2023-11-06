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
        bool groupHeader;
        bool group;
        int groupNum;
        bool active;
        float accAmt = 0;
    
    public:
        Accounts(int accNum, string accName, string accDesc, AccountType accType, bool group, int grpNUM, bool active, bool groupHeader);
        int getAccNum();
        string getAccName();
        string getAccDesc();
        AccountType getAccType();
        bool getHeaderFlag();
        bool getGroup();
        int getGroupNUM();
        bool getActiveStatus();
        virtual void addSubAccounts(Accounts* acc){};
        virtual int removeSubAccounts(int accNum){return 0;};
        virtual bool CheckGroupContains(int subNumber){return false;};
        virtual bool CanDelete(){return true;};

};