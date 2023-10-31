#include <ChartOfAccounts.h>
#include <AccountCreator.h>
#include <iostream>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

ChartOfAccounts::ChartOfAccounts(   Database db,
                                    pair<int,int> assetRange, pair<int,int> liabilityRange,
                                    pair<int,int> equityRange,pair<int,int> revenueRange,
                                    pair<int,int> expenseRange) {

        this->db = db;
        this->assetRange = assetRange;
        this->liabilityRange = liabilityRange;
        this->equityRange = equityRange;
        this->revenueRange = revenueRange;
        this->expenseRange = expenseRange;
        std::cout << "Presistence Status: " << getCOAFromDB() << std::endl;;
    
}

AccountType ChartOfAccounts::getAccountTypeByNum(int accNum){
    if (accNum >= assetRange.first && accNum <= assetRange.second ) return ASSET;
    else if (accNum >= liabilityRange.first && accNum <= liabilityRange.second) return LIABILITY;
    else if (accNum >= equityRange.first && accNum <= equityRange.second) return EQUITY;
    else if (accNum >= revenueRange.first && accNum <= revenueRange.second) return REVENUE;
    else if (accNum >= expenseRange.first && accNum <= expenseRange.second) return EXPENSE;
    else return INVALID;
}

int ChartOfAccounts::CreateAccount(Database db, int accNum, string accName, string accDesc, bool group, int groupID){
    std::string  sql =      "INSERT INTO " + TableName + " "
                            + "(ACCNUM,ACCNAME,ACCDESC,ACCTYPE,ACCGROUP,GRPNUM,ACTIVE) VALUES ( "; 
    if(coa.find(accNum) == coa.end()) {
        AccountType accType = getAccountTypeByNum(accNum);
        if (accType == INVALID) return 3;
        else {
            sql +=  std::to_string(accNum) + ","
                + "'" + accName + "'" + ","
                + "'" + accDesc + "'" + ","
                + "'" + std::to_string(accType) + "'" + ","
                + (group ? "1": "0") + ","
                + (group ? std::to_string(groupID) : "0") + ","
                + "1" + ");";
            if (db.insert(sql) == SQLITE_OK){
                AccountCreator ac;
                coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, accType, group,(group ? groupID : 0),true);
                return 0;
            } else return 1;
        }

    } else return 2;
}

// ADD TESTs
int ChartOfAccounts::getCOAFromDB(){
    std::string sql = "SELECT * FROM COA ORDER BY ACCNUM;";
    Records records;
    AccountCreator ac;
    int ret =  db.query(sql, &records);
    if (coa.size() != 0) return 2;
    if(ret == SQLITE_OK){
        for(auto record: records){
            coa[stoi(record[0])] = ac.CreateAccount(stoi(record[0]), record[1], record[2],(AccountType) stoi(record[3]), (bool) stoi(record[4]),stoi(record[4]),(bool) stoi(record[4]));
        }
        return 0;
    } else return ret;

}



int ChartOfAccounts::getAccount(int accNum, Accounts** acc){
    if(coa.find(accNum) != coa.end()) {
        *acc = coa[accNum];
        return 0;
    } else {
        return 1;
    }

}


// int ChartOfAccounts::updateAccount(Database db, Accounts* acc, AccountFields field, string stringVal, int intVal, float floatVal){
//     int ret;
//     string sql;
//     switch(field){
//         case ACCNUM:
//             if (intVal == NULL) return 2;
//             sql = "UPDATE COA SET ACCNUM = " + std::to_string(intVal) + "  WHERE ACCNUM = " + std::to_string(acc->getAccNum());
//             ret = db.query(sql, NULL);
//             if (ret == 0){
//                 delete acc;
//                 ret = getAccount(db, intVal, &acc);
//             }
//             return ret;
//         case ACCNAME:
//             break;
//         case ACCDESC:
//             break;
//         case ACCTYPE:
//             break;
//         case GROUP:
//             break;
//         case GROUPNUM:
//             break;
//         case ACTIVE:
//             break;
//         case ACCAMT:
//             break;
        
//         default:
//             std::cout << "Error with the name of the field selected: Does not exsist" << std::endl;
//             return -1;

//     }

//     return 1;


// }

                            