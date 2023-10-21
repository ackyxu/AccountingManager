#ifndef CHARTOFACCOUNTS_H
#define CHARTOFACCOUNTS_H

#include <Accounts.h>
#include <AccountType.h>
#include <AccountCreator.h>
#include <unordered_map >

using std::pair;
using std::unordered_map ;

class ChartOfAccounts{

    private:
        unordered_map <int, Accounts*> coa;
        // unordered_map <int, Accounts*> Asset;
        // unordered_map <int, Accounts*> Liability;
        // unordered_map <int, Accounts*> Equity;
        // unordered_map <int, Accounts*> Revenue;
        // unordered_map <int, Accounts*> Expense;
        // unordered_map <AccountType, unordered_map <int, Accounts*>> coa = {{ASSET, Asset},
        //                                                                   {LIABILITY, Liability}, 
        //                                                                   {EQUITY, Equity}, 
        //                                                                   {REVENUE, Revenue}, 
        //                                                                   {EXPENSE, Expense}};
        pair<int,int> assetRange;
        pair<int,int> liabilityRange;
        pair<int,int> equityRange;
        pair<int,int> revenueRange;
        pair<int,int> expenseRange;
        AccountCreator ac;
    

    public:
        ChartOfAccounts(pair<int,int> assetRange = {1000,1999}, pair<int,int> liabilityRange = {2000,2999},
                        pair<int,int> equityRange = {3000,3999},pair<int,int> revenueRange = {4000,4999},
                        pair<int,int> expenseRange = {5000,9999});
        

        int CreateAccount(int accNum, string accName, string accDesc, bool group=false);

        int getAccount(int accNum, Accounts** acc);



};


#endif