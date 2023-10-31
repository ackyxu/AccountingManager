#ifndef CHARTOFACCOUNTS_H
#define CHARTOFACCOUNTS_H

#include <Accounts.h>
#include <AccountType.h>
#include <unordered_map >
#include <Database.h>
#include <AccountFields.h>

using std::pair;
using std::unordered_map ;

class ChartOfAccounts{

    private:
        Database db;
        unordered_map <int, Accounts*> coa;
        pair<int,int> assetRange;
        pair<int,int> liabilityRange;
        pair<int,int> equityRange;
        pair<int,int> revenueRange;
        pair<int,int> expenseRange;
        inline static const std::string TableName = "COA";
        AccountType getAccountTypeByNum(int accnum);
        int getCOAFromDB();
    

    public:
        ChartOfAccounts(Database db,
                        pair<int,int> assetRange = {1000,1999}, pair<int,int> liabilityRange = {2000,2999},
                        pair<int,int> equityRange = {3000,3999},pair<int,int> revenueRange = {4000,4999},
                        pair<int,int> expenseRange = {5000,9999});
        int CreateAccount(Database db, int accNum, string accName, string accDesc, bool group=false, int groupID = 0);
        int getAccount(int accNum, Accounts** acc);
        int updateAccount(Database db, Accounts* acc, AccountFields field, string stringVal = NULL, int intVal = NULL, float floatVal = NULL);

};


#endif