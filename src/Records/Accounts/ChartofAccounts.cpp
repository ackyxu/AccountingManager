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

int ChartOfAccounts::CreateAccount(Database db, int accNum, string accName, string accDesc, bool group, int groupID, bool groupHeader){
    std::string  sql =      "INSERT INTO " + TableName + " "
                            + "(ACCNUM,ACCNAME,ACCDESC,ACCTYPE,ACCHEADER,ACCGROUP,GRPNUM,ACTIVE) VALUES ( "; 
    if(coa.find(accNum) == coa.end()) {
        AccountType accType = getAccountTypeByNum(accNum);
        if (accType == INVALID) return 3;
        else {
            sql +=  std::to_string(accNum) + ","
                + "'" + accName + "'" + ","
                + "'" + accDesc + "'" + ","
                + "'" + std::to_string(accType) + "'" + ","
                + (groupHeader ? "1": "0") + ","
                + (group ? "1": "0") + ","
                + (group ? std::to_string(groupID) : "0") + ","
                + "1" + ");";
            if (db.insert(sql) == SQLITE_OK){
                AccountCreator ac;
                coa[accNum] = ac.CreateAccount(accNum, accName, accDesc, accType, group,(group ? groupID : 0),true);
                return 0;
            } else return 1;

            //TODO: Get AMT value from JE when implemented
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


int ChartOfAccounts::forceSyncCOA(){
    for(auto const& pairs: coa){
        delete pairs.second;
    }
    coa.clear();
    return getCOAFromDB();
}



int ChartOfAccounts::getAccount(int accNum, Accounts** acc){
    if(coa.find(accNum) != coa.end()) {
        *acc = coa[accNum];
        return 0;
    } else {
        return 1;
    }

}


int ChartOfAccounts::updateAccount(Accounts** acc, AccountFields field, string stringVal, int intVal, float floatVal){
    switch(field){
        case ACCNUM:
            if(intVal != NULL){
                return updateACCNUM(acc, intVal);
            } else return -1;
            
        case ACCNAME:
            if(stringVal != ""){
                return updateACCNAME(acc, stringVal);
            } else return -1;
        case ACCDESC:
            if(stringVal != ""){
                return updateACCDESC(acc, stringVal);
            } else return -1;
        case ACCTYPE:
            std::cout << "Please changed the type of the account by changing the Account Number" <<std::endl;
            return 2;
        case GROUP:
            std::cout << "Please changed the Group of the account by changing the Group Number" <<std::endl;
            return 2;
        case GROUPNUM:
            return updateGROUPNUM(acc, intVal);
        case ACTIVE:
            if(intVal == 0 or intVal == 1){
                return updateActiveStatus(acc, intVal);
            } else {
                std::cout << "Check intVal, should be 1 or 0" << std::endl;
            }
        case ACCAMT:
            std::cout << "Cannot set amount from COA" <<std::endl;
            return -1;
        
        default:
            std::cout << "Error with the name of the field selected: Does not exsist" << std::endl;
            return -1;

    }

    return 1;


}




int ChartOfAccounts::updateACCNUM(Accounts** acc, int newAccNum){
        AccountType newAccType = getAccountTypeByNum(newAccNum);
        if(coa.find(newAccNum) == coa.end() && newAccType != INVALID){
            AccountCreator ac;
            std::string sql = "UPDATE " + TableName + " SET ACCNUM = " + std::to_string(newAccNum) + ",  ACCTYPE = " + 
                                    std::to_string((int)newAccType) + " WHERE ACCNUM = " + std::to_string((*acc)->getAccNum()) +";";
            int ret = db.query(sql, NULL);
            if(ret == SQLITE_OK){
                Accounts* newACC = ac.CreateAccount(newAccNum, (*acc)->getAccName(), (*acc)->getAccDesc(), 
                                                    newAccType, (*acc)->getGroup(), (*acc)->getGroupNUM(), (*acc)->getActiveStatus());
                coa.erase((*acc)->getAccNum());
                delete *acc;
                coa[newAccNum] = newACC;
                *acc = newACC;
                return 0;
            } else return ret;

        } else if (newAccType == INVALID) return 3;
        else return 2;

}


int ChartOfAccounts::updateACCNAME(Accounts** acc, string newAccName){
        if(newAccName != ""){
            AccountCreator ac;
            std::string sql = "UPDATE " + TableName + " SET ACCNAME = '" + newAccName +  "' WHERE ACCNUM = " + std::to_string((*acc)->getAccNum()) +";";
            int ret = db.query(sql, NULL);
            if(ret == SQLITE_OK){
                Accounts* newACC = ac.CreateAccount((*acc)->getAccNum(), newAccName, (*acc)->getAccDesc(), 
                                                    (*acc)->getAccType(), (*acc)->getGroup(), (*acc)->getGroupNUM(), (*acc)->getActiveStatus());
                int oldAccNum = (*acc)->getAccNum();
                coa.erase((*acc)->getAccNum());
                delete *acc;
                coa[oldAccNum] = newACC;
                *acc = newACC;
                return 0;
            } else return ret;

        } else return 2;
  
}



int ChartOfAccounts::updateACCDESC(Accounts** acc, string newAccDesc){
        if(newAccDesc != ""){
            AccountCreator ac;
            std::string sql = "UPDATE " + TableName + " SET ACCDESC = '" + newAccDesc +  "' WHERE ACCNUM = " + std::to_string((*acc)->getAccNum()) +";";
            int ret = db.query(sql, NULL);
            if(ret == SQLITE_OK){
                Accounts* newACC = ac.CreateAccount((*acc)->getAccNum(), (*acc)->getAccDesc(), newAccDesc, 
                                                    (*acc)->getAccType(), (*acc)->getGroup(), (*acc)->getGroupNUM(), (*acc)->getActiveStatus());
                int oldAccNum = (*acc)->getAccNum();
                coa.erase((*acc)->getAccNum());
                delete *acc;
                coa[oldAccNum] = newACC;
                *acc = newACC;
                return 0;
            } else return ret;

        } else return 2;
  
}


int ChartOfAccounts::updateGROUPNUM(Accounts** acc, int newGroupNum){
    int oldAccNum = (*acc)->getAccNum();
    if(newGroupNum == 0){
        AccountCreator ac;
        std::string sql = "UPDATE " + TableName + " SET ACCGROUP = 0, GRPNUM = 0 WHERE ACCNUM = " + std::to_string(oldAccNum) +";";
        int ret = db.query(sql, NULL);
        if(ret == SQLITE_OK){
            Accounts* newACC = ac.CreateAccount((*acc)->getAccNum(), (*acc)->getAccDesc(), (*acc)->getAccDesc(), 
                                                (*acc)->getAccType(), false, 0, (*acc)->getActiveStatus());
            coa.erase((*acc)->getAccNum());
            delete *acc;
            coa[oldAccNum] = newACC;
            *acc = newACC;
            return 0;
        } else return ret;

    } else if(coa.find(newGroupNum) != coa.end()) {
        if (newGroupNum >= oldAccNum or getAccountTypeByNum(newGroupNum) != getAccountTypeByNum(oldAccNum)) return 3;
        AccountCreator ac;
        std::string sql = "UPDATE " + TableName + " SET ACCGROUP = 1, GRPNUM = " + std::to_string(newGroupNum) + " WHERE ACCNUM = " + std::to_string(oldAccNum) +";";
        int ret = db.query(sql, NULL);
        
        if(ret == SQLITE_OK){

            Accounts* newACC = ac.CreateAccount((*acc)->getAccNum(), (*acc)->getAccDesc(), (*acc)->getAccDesc(), 
                                                (*acc)->getAccType(), true, newGroupNum, (*acc)->getActiveStatus());
            
            coa.erase(oldAccNum);
            delete *acc;
            coa[oldAccNum] = newACC;
            *acc = newACC;
            return 0;
        } else return ret;

    } else return 2;
}

// Takes in a int that is 1 or 0, to represent bool
int ChartOfAccounts::updateActiveStatus(Accounts** acc, int activeStatus){
    if (activeStatus == 1 or activeStatus == 0){  
        if ((bool)activeStatus == (*acc)->getActiveStatus()) return 3;
        AccountCreator ac;
        std::string sql = "UPDATE " + TableName + " SET ACTIVE = " + std::to_string(activeStatus) +  " WHERE ACCNUM = " + std::to_string((*acc)->getAccNum()) +";";
        int ret = db.query(sql, NULL);
  
        if (ret == SQLITE_OK){
            Accounts* newACC = ac.CreateAccount((*acc)->getAccNum(), (*acc)->getAccDesc(), (*acc)->getAccDesc(), 
                                    (*acc)->getAccType(), (*acc)->getGroup(), (*acc)->getGroupNUM(), (bool)activeStatus);
            int oldAccNum = (*acc)->getAccNum();
            coa.erase(oldAccNum);
            delete *acc;
            coa[oldAccNum] = newACC;
            *acc = newACC;
            return 0;

        } else return ret;

    } else return 2;
}

                            