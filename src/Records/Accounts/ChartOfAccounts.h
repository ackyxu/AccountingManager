#include <Accounts.h>
#include <AccountCreator.h>
#include <map>

using std::pair;
using std::map;

class ChartofAccounts{

    private:
        static enum AccountType {ASSET, LIABILITY, EQUITY, REVENUE, EXPENSE};
        map<int, Accounts> Asset;
        map<int, Accounts> Liability;
        map<int, Accounts> Equity;
        map<int, Accounts> Revenue;
        map<int, Accounts> Expense;
        pair<int,int> assetRange;
        pair<int,int> liaRange;
        pair<int,int> equityRange;
        pair<int,int> revenueRange;
        pair<int,int> expenseRange;
    

    public:
        ChartofAccounts(pair<int,int> assetRange = {0,1999}, pair<int,int> liaRange = {2000,2999},
                        pair<int,int> equityRange = {3000,3999},pair<int,int> revenueRange = {4000,4999},
                        pair<int,int> expenseRange = {5000,9999});
        

        void CreateAccount(int accNum, string accName, string accDesc, string accType);



};