#include <ChartOfAccounts.h>
#include <AccountCreator.h>
#include <iostream>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

ChartOfAccounts::ChartOfAccounts(   pair<int,int> assetRange, pair<int,int> liabilityRange,
                                    pair<int,int> equityRange,pair<int,int> revenueRange,
                                    pair<int,int> expenseRange) {

        this->assetRange = assetRange;
        this->liabilityRange = liabilityRange;
        this->equityRange = equityRange;
        this->revenueRange = revenueRange;
        this->expenseRange = expenseRange;
    
}

int ChartOfAccounts::CreateAccount(Database db, int accNum, string accName, string accDesc, bool group, int groupID){
    std::string  sql =      "INSERT INTO " + TableName + " "
                            + "(ACCNUM,ACCNAME,ACCDESC,ACCTYPE,ACCGROUP,GRPNUM,ACTIVE) VALUES ( "; 
    if (accNum >= assetRange.first && accNum <= assetRange.second ) {
        if(coa.find(accNum) == coa.end()) {
            // coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, ASSET, group);
            sql +=  std::to_string(accNum) + ","
                    + "'" + accName + "'" + ","
                    + "'" + accDesc + "'" + ","
                    + "'" + std::to_string(ASSET) + "'" + ","
                    + (group ? "1": "0") + ","
                    + (group ? std::to_string(groupID) : "0") + ","
                    + "1" + ");";

            return (db.insert(sql) == SQLITE_OK) ? 0:1;
        }
        else return 1;
    }

    else if (accNum >= liabilityRange.first && accNum <= liabilityRange.second){
        if(coa.find(accNum) == coa.end()) {
            // coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, LIABILITY, group);
            sql +=  std::to_string(accNum) + ","
                    + "'" + accName + "'" + ","
                    + "'" + accDesc + "'" + ","
                    + "'" + std::to_string(LIABILITY) + "'" + ","
                    + (group ? "1": "0") + ","
                    + (group ? std::to_string(groupID) : "0") + ","
                    + "1" + ");";
            return (db.insert(sql) == SQLITE_OK) ? 0:1;
        }
        else return 1;
    }

    else if (accNum >= equityRange.first && accNum <= equityRange.second){
        if(coa.find(accNum) == coa.end()) {
            // coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, EQUITY, group);
            sql +=  std::to_string(accNum) + ","
                    + "'" + accName + "'" + ","
                    + "'" + accDesc + "'" + ","
                    + "'" + std::to_string(EQUITY) + "'" + ","
                    + (group ? "1": "0") + ","
                    + (group ? std::to_string(groupID) : "0") + ","
                    + "1" + ");";
            return (db.insert(sql) == SQLITE_OK) ? 0:1;
        }
        else return 1;

    }

    else if (accNum >= revenueRange.first && accNum <= revenueRange.second){
        if(coa.find(accNum) == coa.end()) {
            // coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, REVENUE, group);
            sql +=  std::to_string(accNum) + ","
                    + "'" + accName + "'" + ","
                    + "'" + accDesc + "'" + ","
                    + "'" + std::to_string(REVENUE) + "'" + ","
                    + (group ? "1": "0") + ","
                    + (group ? std::to_string(groupID) : "0") + ","
                    + "1" + ");";
            return (db.insert(sql) == SQLITE_OK) ? 0:1;
        }
        else return 1;

    }
     
    else if (accNum >= expenseRange.first && accNum <= expenseRange.second){
        if(coa.find(accNum) == coa.end()) {
            // coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, EXPENSE, group);
            sql +=  std::to_string(accNum) + ","
                    + "'" + accName + "'" + ","
                    + "'" + accDesc + "'" + ","
                    + "'" + std::to_string(EXPENSE) + "'" + ","
                    + (group ? "1": "0") + ","
                    + (group ? std::to_string(groupID) : "0") + ","
                    + "1" + ");";
            return (db.insert(sql) == SQLITE_OK) ? 0:1;
        }
        else return 1;
    } else return 2;

}


int ChartOfAccounts::getAccount(Database db,int accNum, Accounts** acc){
    std::string sql = "SELECT * FROM COA WHERE ACCNUM = " + std::to_string(accNum) + ";";
    Records records = db.query(sql);
    if(records.size() == 1) {
        AccountCreator ac;
        Record record = records[0];
        *acc = ac.CreateAccount(accNum, record[1], record[2],(AccountType) stoi(record[3]), (bool) stoi(record[4]),stoi(record[4]),(bool) stoi(record[4]));
        return 0;
    } else {
        return 1;
    }

}

                            