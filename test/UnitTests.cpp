#include <gtest/gtest.h>
#include <sqlite3.h>
#include <Database.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <AccountFields.h>
#include <AccountType.h>
#include <ChartOfAccounts.h>
#include <CompositeAccounts.h>



class DatabaseTest : public ::testing::Test {

    protected:
        Database db;
        std::string filename = "test.db";
        std::vector<std::string> databaseNames;
        void TearDown() override {
            db.closeDatabase();
            for (auto name:databaseNames){
                remove(name.c_str());
            }
        }


};

TEST_F(DatabaseTest, DatabaseCloseTest){
    databaseNames.push_back(filename);
    ASSERT_EQ(db.closeDatabase(), 1) << "There should be not database connection established as this point";
    ASSERT_EQ(db.createDatabase(filename), 0) << "Failed to create Database";
    ASSERT_EQ(db.closeDatabase(), SQLITE_OK) << "The connection should have closed successfully here";

}

TEST_F(DatabaseTest, DatabaseDoesNotExsistsTest){
    ASSERT_EQ(db.connectDatabase(filename),1) << db.connectDatabase(filename) << std::endl;
}

TEST_F(DatabaseTest, DatabaseAlreadyConnectedTest){
    databaseNames.push_back(filename);
    ASSERT_EQ(db.createDatabase(filename), 0) << "Failed to create Database";
    ASSERT_EQ(db.connectDatabase(filename),-1) << "Trying to connect to the already created database";
}

TEST_F(DatabaseTest, DatabaseTwoDatabaseFileTest){
    
    databaseNames.push_back(filename);
    std::string filename2 = "test2.db";
    databaseNames.push_back(filename2);
    ASSERT_EQ(db.createDatabase(filename), 0) << "Failed to create Database";
    ASSERT_EQ(db.createDatabase(filename2), -1) << "Need To Close First";
    ASSERT_EQ(db.closeDatabase(), SQLITE_OK);
    ASSERT_EQ(db.createDatabase(filename), 2) << "Database Already Exsist";
    ASSERT_EQ(db.createDatabase(filename2), 0) << "Failed to create Database";
    ASSERT_EQ(db.closeDatabase(), SQLITE_OK);
    ASSERT_EQ(db.connectDatabase(filename),0) << "Cannot Connect";
}

class ChartOfAccountsTest : public :: testing ::Test {

    protected:

        Database db;
        std::string filename = "test.db";
        std::vector<std::string> databaseNames;
        Accounts* acc;
        ChartOfAccounts* coa;
        
        int status;
        
        void SetUp() override{
            db.createDatabase(filename);
            coa = new ChartOfAccounts(db);
            
        }
        
        void TearDown() override {
            db.closeDatabase();
            remove(filename.c_str());
            delete coa;
        }
};


TEST_F(ChartOfAccountsTest, COA_Add_Asset){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Cash","BankAcc"),0);
    ASSERT_EQ(coa->CreateAccount(db,1500,"Equipment","Equipment Capital Asset"),0);
    ASSERT_EQ(coa->CreateAccount(db,1999,"Goodwill","Goodwill Account"),0);
    ASSERT_EQ(coa->CreateAccount(db,2000, "TestLia", "Test of liability"),0);

    
    // Check for acc# 1000
    status = coa->getAccount(1000,&acc);
    
    ASSERT_EQ(status,0) << "Cannot find the account 1000, skipping the account checks";
    
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 1000);
        ASSERT_EQ(acc->getAccName(), "Cash");
        ASSERT_EQ(acc->getAccDesc(), "BankAcc");
        ASSERT_EQ(acc->getAccType(), ASSET);
    }

    // Check for acc# 1500
    status = coa->getAccount(1500,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 1500, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 1500);
        ASSERT_EQ(acc->getAccName(), "Equipment");
        ASSERT_EQ(acc->getAccDesc(), "Equipment Capital Asset");
        ASSERT_EQ(acc->getAccType(), ASSET);
    }


    // Check for acc# 1999
    status = coa->getAccount(1999,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 1999, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 1999);
        ASSERT_EQ(acc->getAccName(), "Goodwill");
        ASSERT_EQ(acc->getAccDesc(), "Goodwill Account");
        ASSERT_EQ(acc->getAccType(), ASSET);
    }


    status = coa->getAccount(2000,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 2000, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 2000);
        ASSERT_EQ(acc->getAccName(), "TestLia");
        ASSERT_EQ(acc->getAccDesc(), "Test of liability");
        ASSERT_EQ(acc->getAccType(), LIABILITY);
    }


}



TEST_F(ChartOfAccountsTest, COA_Add_Liability){
    ASSERT_EQ(coa->CreateAccount(db,2000,"AP","Accounts Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,2500,"Debt","Bank Debt"),0);
    ASSERT_EQ(coa->CreateAccount(db,2999,"Taxes Payable","Corperate Taxes Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,3000, "TestEQ", "Test of equity"),0);

    
    // Check for acc# 2000
    status = coa->getAccount(2000,&acc);
    
    ASSERT_EQ(status,0) << "Cannot find the account 2000, skipping the account checks";
    
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 2000);
        ASSERT_EQ(acc->getAccName(), "AP");
        ASSERT_EQ(acc->getAccDesc(), "Accounts Payable");
        ASSERT_EQ(acc->getAccType(), LIABILITY);
    }

    // Check for acc# 2500
    status = coa->getAccount(2500,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 2500, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 2500);
        ASSERT_EQ(acc->getAccName(), "Debt");
        ASSERT_EQ(acc->getAccDesc(), "Bank Debt");
        ASSERT_EQ(acc->getAccType(), LIABILITY);
    }


    // Check for acc# 2999
    status = coa->getAccount(2999,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 2999, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 2999);
        ASSERT_EQ(acc->getAccName(), "Taxes Payable");
        ASSERT_EQ(acc->getAccDesc(), "Corperate Taxes Payable");
        ASSERT_EQ(acc->getAccType(), LIABILITY);
    }


    status = coa->getAccount(3000,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 3000, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 3000);
        ASSERT_EQ(acc->getAccName(), "TestEQ");
        ASSERT_EQ(acc->getAccDesc(), "Test of equity");
        ASSERT_EQ(acc->getAccType(), EQUITY);
    }


}

TEST_F(ChartOfAccountsTest, COA_Add_Equity){
    ASSERT_EQ(coa->CreateAccount(db,3000,"AP","Accounts Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,3500,"Debt","Bank Debt"),0);
    ASSERT_EQ(coa->CreateAccount(db,3999,"Taxes Payable","Corperate Taxes Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,4000, "TestEQ", "Test of equity"),0);

    
    // Check for acc# 3000
    status = coa->getAccount(3000,&acc);
    
    ASSERT_EQ(status,0) << "Cannot find the account 3000, skipping the account checks";
    
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 3000);
        ASSERT_EQ(acc->getAccName(), "AP");
        ASSERT_EQ(acc->getAccDesc(), "Accounts Payable");
        ASSERT_EQ(acc->getAccType(), EQUITY);
    }

    // Check for acc# 3500
    status = coa->getAccount(3500,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 3500, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 3500);
        ASSERT_EQ(acc->getAccName(), "Debt");
        ASSERT_EQ(acc->getAccDesc(), "Bank Debt");
        ASSERT_EQ(acc->getAccType(), EQUITY);
    }


    // Check for acc# 3999
    status = coa->getAccount(3999,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 3999, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 3999);
        ASSERT_EQ(acc->getAccName(), "Taxes Payable");
        ASSERT_EQ(acc->getAccDesc(), "Corperate Taxes Payable");
        ASSERT_EQ(acc->getAccType(), EQUITY);
    }


    status = coa->getAccount(4000,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 4000, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 4000);
        ASSERT_EQ(acc->getAccName(), "TestEQ");
        ASSERT_EQ(acc->getAccDesc(), "Test of equity");
        ASSERT_EQ(acc->getAccType(), REVENUE);
    }


}



TEST_F(ChartOfAccountsTest, COA_Add_Revenue){
    ASSERT_EQ(coa->CreateAccount(db,4000,"AP","Accounts Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,4500,"Debt","Bank Debt"),0);
    ASSERT_EQ(coa->CreateAccount(db,4999,"Taxes Payable","Corperate Taxes Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,5000, "TestEQ", "Test of equity"),0);

    
    // Check for acc# 4000
    status = coa->getAccount(4000,&acc);
    
    ASSERT_EQ(status,0) << "Cannot find the account 4000, skipping the account checks";
    
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 4000);
        ASSERT_EQ(acc->getAccName(), "AP");
        ASSERT_EQ(acc->getAccDesc(), "Accounts Payable");
        ASSERT_EQ(acc->getAccType(), REVENUE);
    }

    // Check for acc# 4500
    status = coa->getAccount(4500,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 4500, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 4500);
        ASSERT_EQ(acc->getAccName(), "Debt");
        ASSERT_EQ(acc->getAccDesc(), "Bank Debt");
        ASSERT_EQ(acc->getAccType(), REVENUE);
    }


    // Check for acc# 4999
    status = coa->getAccount(4999,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 4999, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 4999);
        ASSERT_EQ(acc->getAccName(), "Taxes Payable");
        ASSERT_EQ(acc->getAccDesc(), "Corperate Taxes Payable");
        ASSERT_EQ(acc->getAccType(), REVENUE);
    }


    status = coa->getAccount(5000,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 5000, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 5000);
        ASSERT_EQ(acc->getAccName(), "TestEQ");
        ASSERT_EQ(acc->getAccDesc(), "Test of equity");
        ASSERT_EQ(acc->getAccType(), EXPENSE);
    }


}

TEST_F(ChartOfAccountsTest, COA_Add_Expense){
    ASSERT_EQ(coa->CreateAccount(db,5000,"AP","Accounts Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,5503,"Debt","Bank Debt"),0);
    ASSERT_EQ(coa->CreateAccount(db,9999,"Taxes Payable","Corperate Taxes Payable"),0);
    ASSERT_EQ(coa->CreateAccount(db,6234, "TestEQ", "Test of equity"),0);
    ASSERT_EQ(coa->CreateAccount(db,10000, "TestEQ", "Test of equity"),3) << "acc 10 000 should be out of range";


    
    // Check for acc# 5000
    status = coa->getAccount(5000,&acc);
    
    ASSERT_EQ(status,0) << "Cannot find the account 5000, skipping the account checks";
    
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 5000);
        ASSERT_EQ(acc->getAccName(), "AP");
        ASSERT_EQ(acc->getAccDesc(), "Accounts Payable");
        ASSERT_EQ(acc->getAccType(), EXPENSE);
    }

    // Check for acc# 5503
    status = coa->getAccount(5503,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 5503, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 5503);
        ASSERT_EQ(acc->getAccName(), "Debt");
        ASSERT_EQ(acc->getAccDesc(), "Bank Debt");
        ASSERT_EQ(acc->getAccType(), EXPENSE);
    }


    // Check for acc# 9999
    status = coa->getAccount(9999,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 9999, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 9999);
        ASSERT_EQ(acc->getAccName(), "Taxes Payable");
        ASSERT_EQ(acc->getAccDesc(), "Corperate Taxes Payable");
        ASSERT_EQ(acc->getAccType(), EXPENSE);
    }


    status = coa->getAccount(6234,&acc);
    ASSERT_EQ(status,0) << "Cannot find account 6234, skipping the account checks";
    if (status == 0) {
        ASSERT_EQ(acc->getAccNum(), 6234);
        ASSERT_EQ(acc->getAccName(), "TestEQ");
        ASSERT_EQ(acc->getAccDesc(), "Test of equity");
        ASSERT_EQ(acc->getAccType(), EXPENSE);
    }


}

TEST_F(ChartOfAccountsTest, COA_EmptyList){
    ASSERT_EQ(coa->getAccount(1000,&acc),1);
    ASSERT_EQ(coa->getAccount(2353,&acc),1);
    ASSERT_EQ(coa->getAccount(3478,&acc),1);
    ASSERT_EQ(coa->getAccount(4345,&acc),1);
    ASSERT_EQ(coa->getAccount(5834,&acc),1);
}

TEST_F(ChartOfAccountsTest, COA_CreateAccNumberAlreadyExsists){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),0);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),0);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),0);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),0);


    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),2);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),2);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),2);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),2);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),2);

}


TEST_F(ChartOfAccountsTest, COA_CreateGroupHeaders){
    ASSERT_EQ(coa->CreateAccount(db,1000,"AssetHeader","AssetHeader",false,0,true),0);
    ASSERT_EQ(coa->CreateAccount(db,1500,"AssetSub","AssetSub",true,1000),0);
    ASSERT_EQ(coa->CreateAccount(db,2500,"AssetSub","AssetSub",true,1000),3);
    ASSERT_EQ(coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1000,true),0);
    ASSERT_EQ(coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600),0);


    coa->getAccount(1000, &acc);
    ASSERT_TRUE(acc->CheckGroupContains(1500));
    ASSERT_FALSE(acc->CheckGroupContains(2500));
    ASSERT_TRUE(acc->CheckGroupContains(1600));

    coa->getAccount(1600, &acc);
    ASSERT_TRUE(acc->CheckGroupContains(1650));

}


TEST_F(ChartOfAccountsTest, COA_DataPresistenceAccounts){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);
    ASSERT_EQ(coa->CreateAccount(db,1500,"AssetHeader","AssetHeader",false,0,true),0);
    ASSERT_EQ(coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1500,true),0);
    ASSERT_EQ(coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600),0);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),0);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),0);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),0);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),0);

    // Close the current COA and DB
    db.closeDatabase();
    delete coa;

    db.connectDatabase(filename);
    coa = new ChartOfAccounts(db);

    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(coa->getAccount(1500,&acc),0);
    ASSERT_EQ(coa->getAccount(1600,&acc),0);
    ASSERT_EQ(coa->getAccount(1650,&acc),0);
    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(coa->getAccount(5000,&acc),0);

    coa->getAccount(1600, &acc);
    ASSERT_TRUE(acc->getHeaderFlag());
    ASSERT_TRUE(acc->CheckGroupContains(1650));


    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),2);
    ASSERT_EQ(coa->CreateAccount(db,1500,"AssetHeader","AssetHeader",false,0,true),2);
    ASSERT_EQ(coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1500,true),2);
    ASSERT_EQ(coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600),2);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),2);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),2);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),2);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),2);

}



TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_ACCNUM){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);


    // Check ACCNUM update within same Type 
    coa->getAccount(1000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",1500),0);
    ASSERT_EQ(coa->getAccount(1000,&acc),1);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",NULL),-1);

    // ASSERT_EQ(coa->getAccount(1500,&acc),0);
    ASSERT_EQ(acc->getAccNum(), 1500);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), ASSET);

    // Reset Acc 1000
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);

    // Check that duplciateACCNUM update is not possible
    coa->getAccount(1000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",1500),2);
    ASSERT_EQ(coa->getAccount(1000,&acc),0) << "Nothing should be updated since we don't allow duplicate ACCNUM";


    // Check ACCNUM update with different Type
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",2500),0);
    ASSERT_EQ(coa->getAccount(1000,&acc),1);
    ASSERT_EQ(coa->getAccount(2500,&acc),0);
    ASSERT_EQ(acc->getAccNum(), 2500);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), LIABILITY);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",3500),0);
    ASSERT_EQ(coa->getAccount(2500,&acc),1);
    ASSERT_EQ(coa->getAccount(3500,&acc),0);
    ASSERT_EQ(acc->getAccNum(), 3500);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), EQUITY);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",4500),0);
    ASSERT_EQ(coa->getAccount(3500,&acc),1);
    ASSERT_EQ(coa->getAccount(4500,&acc),0);
    ASSERT_EQ(acc->getAccNum(), 4500);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), REVENUE);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",5500),0);
    ASSERT_EQ(coa->getAccount(4500,&acc),1);
    ASSERT_EQ(acc->getAccNum(), 5500);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), EXPENSE);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",9999),0);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",10000),3);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",9999),2);
    ASSERT_EQ(acc->getAccNum(), 9999);


    coa->forceSyncCOA();
    ASSERT_EQ(coa->getAccount(9999,&acc),0);
    ASSERT_EQ(acc->getAccNum(), 9999);
    ASSERT_EQ(acc->getAccName(), "Asset");
    ASSERT_EQ(acc->getAccDesc(), "Asset");
    ASSERT_EQ(acc->getAccType(), EXPENSE);
}

TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_ACCNUM_Boundaries){

    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);
    coa->getAccount(1000,&acc);

    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",999),3);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",1001),0);
    ASSERT_EQ(acc->getAccType(), ASSET);

    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",1999),0);
    ASSERT_EQ(coa->getAccount(1999,&acc),0);
    ASSERT_EQ(acc->getAccType(), ASSET);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",2000),0);
    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(acc->getAccType(), LIABILITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",1999),0);
    ASSERT_EQ(coa->getAccount(1999,&acc),0);
    ASSERT_EQ(acc->getAccType(), ASSET);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",2001),0);
    ASSERT_EQ(coa->getAccount(2001,&acc),0);
    ASSERT_EQ(acc->getAccType(), LIABILITY);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",2999),0);
    ASSERT_EQ(coa->getAccount(2999,&acc),0);
    ASSERT_EQ(acc->getAccType(), LIABILITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",3000),0);
    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(acc->getAccType(), EQUITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",2999),0);
    ASSERT_EQ(coa->getAccount(2999,&acc),0);
    ASSERT_EQ(acc->getAccType(), LIABILITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",3001),0);
    ASSERT_EQ(coa->getAccount(3001,&acc),0);
    ASSERT_EQ(acc->getAccType(), EQUITY);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",3999),0);
    ASSERT_EQ(coa->getAccount(3999,&acc),0);
    ASSERT_EQ(acc->getAccType(), EQUITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",4000),0);
    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(acc->getAccType(), REVENUE);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",3999),0);
    ASSERT_EQ(coa->getAccount(3999,&acc),0);
    ASSERT_EQ(acc->getAccType(), EQUITY);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",4001),0);
    ASSERT_EQ(coa->getAccount(4001,&acc),0);
    ASSERT_EQ(acc->getAccType(), REVENUE);


    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",4999),0);
    ASSERT_EQ(coa->getAccount(4999,&acc),0);
    ASSERT_EQ(acc->getAccType(), REVENUE);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",5000),0);
    ASSERT_EQ(coa->getAccount(5000,&acc),0);
    ASSERT_EQ(acc->getAccType(), EXPENSE);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",4999),0);
    ASSERT_EQ(coa->getAccount(4999,&acc),0);
    ASSERT_EQ(acc->getAccType(), REVENUE);
    ASSERT_EQ(coa->updateAccount(&acc,ACCNUM,"",5001),0);
    ASSERT_EQ(coa->getAccount(5001,&acc),0);
    ASSERT_EQ(acc->getAccType(), EXPENSE);

}

TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_ACCNAME){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),0);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),0);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),0);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),0);


    coa->getAccount(1000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCNAME, "NewAsset"),0);
    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewAsset");


    coa->getAccount(2000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCNAME, "NewLia"),0);
    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewLia");

    coa->getAccount(3000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCNAME, "NewEquity"),0);
    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewEquity");
    
    coa->getAccount(4000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCNAME, "NewRev"),0);
    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewRev");

    coa->getAccount(5000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCNAME, "NewExp"),0);
    ASSERT_EQ(coa->getAccount(5000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewExp");


    coa->forceSyncCOA();
    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewAsset");   

    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewLia");

    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewEquity");

    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewRev");

    ASSERT_EQ(coa->getAccount(5000,&acc),0);
    ASSERT_EQ(acc->getAccName(), "NewExp");

}


TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_ACCDESC){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","Asset"),0);
    ASSERT_EQ(coa->CreateAccount(db,2000,"Liability","Liability"),0);
    ASSERT_EQ(coa->CreateAccount(db,3000,"Equity","Equity"),0);
    ASSERT_EQ(coa->CreateAccount(db,4000,"Revenue","Revenue"),0);
    ASSERT_EQ(coa->CreateAccount(db,5000,"Exepense","Exepense"),0);


    coa->getAccount(1000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCDESC, "NewAssetDesc"),0);
    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewAssetDesc");
    ASSERT_EQ(acc->getAccName(), "Asset");


    coa->getAccount(2000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCDESC, "NewLiaDesc"),0);
    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewLiaDesc");

    coa->getAccount(3000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCDESC, "NewEquityDesc"),0);
    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewEquityDesc");
    
    coa->getAccount(4000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCDESC, "NewRevDesc"),0);
    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewRevDesc");

    coa->getAccount(5000,&acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACCDESC, "NewExpDesc"),0);
    ASSERT_EQ(coa->getAccount(5000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewExpDesc");


    coa->forceSyncCOA();
    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewAssetDesc");   

    ASSERT_EQ(coa->getAccount(2000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewLiaDesc");

    ASSERT_EQ(coa->getAccount(3000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewEquityDesc");

    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewRevDesc");

    ASSERT_EQ(coa->getAccount(5000,&acc),0);
    ASSERT_EQ(acc->getAccDesc(), "NewExpDesc");

}


TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_GROUPNUM){
    ASSERT_EQ(coa->CreateAccount(db,1000,"AssetGrp","AssetGrp",false, 0, true),0);
    ASSERT_EQ(coa->CreateAccount(db,1100,"AssetGrp2","AssetGrp"),0);
    ASSERT_EQ(coa->CreateAccount(db,1500,"Asset","Asset"),0);

    coa->getAccount(1500, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",1100), 3);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",1000), 0);
    ASSERT_TRUE(acc->getGroup());
    ASSERT_EQ(acc->getGroupNUM(), 1000);
    coa->getAccount(1000, &acc);
    ASSERT_TRUE(acc->CheckGroupContains(1500));
    
    
    coa->getAccount(1500, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",0), 0);
    ASSERT_FALSE(acc->getGroup());
    ASSERT_EQ(acc->getGroupNUM(), 0);
    
    
    coa->getAccount(1000, &acc);
    ASSERT_FALSE(acc->CheckGroupContains(1500));

    coa->getAccount(1500, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",1500), 3) << "Cannot be same number";

    ASSERT_EQ(coa->CreateAccount(db,1300,"AssetSub","AssetSub"),0);
    coa->getAccount(1300, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",1500), 3) << "Number must be greater";

    ASSERT_EQ(coa->CreateAccount(db,2500,"LiaSub","LiaSub"),0);
    coa->getAccount(2500, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, GROUPNUM,"",1500), 3) << "Number must be in same accounting type";

    

}


TEST_F(ChartOfAccountsTest, COA_UpdateAccounts_ACTIVE){
    ASSERT_EQ(coa->CreateAccount(db,1000,"Asset","AssetGrp"),0);


    coa->getAccount(1000, &acc);
    ASSERT_EQ(coa->updateAccount(&acc, ACTIVE, "", 1), 3) << "Should return 3 if status was the same already";
    ASSERT_EQ(coa->updateAccount(&acc, ACTIVE, "", 0), 0) << "Failing on updating from true to false";
    ASSERT_EQ(coa->updateAccount(&acc, ACTIVE, "", 0), 3) << "Should return 3 if status was the same already";
    ASSERT_EQ(coa->updateAccount(&acc ,ACTIVE, "", 1), 0) << "Failing on updating from false to true";
}


TEST_F(ChartOfAccountsTest, COA_DeleteAccounts){

    coa->CreateAccount(db,1000,"Asset","Asset");
    coa->CreateAccount(db,1500,"AssetHeader","AssetHeader",false,0,true);
    coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1500,true);
    coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600);
    coa->CreateAccount(db,2000,"Liability","Liability");
    coa->CreateAccount(db,3000,"Equity","Equity");
    coa->CreateAccount(db,4000,"Revenue","Revenue");
    coa->CreateAccount(db,5000,"Exepense","Exepense");

    ASSERT_EQ(coa->deleteAccount(2000), 0) << "Should have successfully deleted a non-group account";
    ASSERT_EQ(coa->deleteAccount(2000), 2) << "Already deleted the non-group account, shouldn't be able to do it again";
    ASSERT_EQ(coa->deleteAccount(3000), 0) << "Should have successfully deleted a non-group account";
    
    ASSERT_EQ(coa->deleteAccount(1500), 2) << "Shouldn't be able to delete a group-header account without first deleting/removing sub accounts";
    ASSERT_EQ(coa->deleteAccount(1650), 0) << "Should have successfully deleted a non-group account";
    ASSERT_EQ(coa->deleteAccount(1500), 2) << "Shouldn't be able to delete a group-header account without first deleting/removing sub accounts (1650)";
    ASSERT_EQ(coa->deleteAccount(1600), 0) << "Should have successfully deleted a group account with no sub accounts";
    ASSERT_EQ(coa->deleteAccount(1500), 0) << "Finally, should have successfully deleted a group account with no sub accounts";


    // Check presistence, aka check that the datebase has been updated correctly
    db.closeDatabase();
    delete coa;

    db.connectDatabase(filename);
    coa = new ChartOfAccounts(db);
    ASSERT_EQ(coa->getAccount(1500,&acc),1);
    ASSERT_EQ(coa->getAccount(1600,&acc),1);
    ASSERT_EQ(coa->getAccount(1650,&acc),1);
    ASSERT_EQ(coa->getAccount(1000,&acc),0);
    ASSERT_EQ(coa->getAccount(4000,&acc),0);
    ASSERT_EQ(coa->getAccount(5000,&acc),0);

}

TEST_F(ChartOfAccountsTest, CompositeAccounts_GetSubAccNum){

    coa->CreateAccount(db,1000,"Asset","Asset");
    coa->CreateAccount(db,1500,"AssetHeader","AssetHeader",false,0,true);
    coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1500,true);
    coa->CreateAccount(db,1700,"AssetHeaderSub","AssetHeaderSub",true,1500);
    coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600);

    bool found = false;
    coa->getAccount(1500, &acc);
    std::vector<int> subAccountNums = acc->ListSubAccountNum();

    for(auto accNum: subAccountNums){
        if (accNum == 1600){
            found = true;
        }
    }

    ASSERT_TRUE(found) << "Finding accNum 1600";

    found = false;
    for(auto accNum: subAccountNums){
        if (accNum == 1700){
            found = true;
        }
    }

    ASSERT_TRUE(found) << "Finding accNum 1700";

    found = false;
    for(auto accNum: subAccountNums){
        if (accNum == 1650){
            found = true;
        }
    }

    ASSERT_FALSE(found) << "Finding accNum 1650 (sub acc for 1600)";

}


TEST_F(ChartOfAccountsTest, CompositeAccounts_GetHeaderSubAccNum){

    coa->CreateAccount(db,1000,"Asset","Asset");
    coa->CreateAccount(db,1500,"AssetHeader","AssetHeader",false,0,true);
    coa->CreateAccount(db,1600,"AssetHeaderSub","AssetHeaderSub",true,1500,true);
    coa->CreateAccount(db,1700,"AssetHeaderSub","AssetHeaderSub",true,1500);
    coa->CreateAccount(db,1650,"AssetHeaderSubSub","AssetHeaderSubSub",true,1600);

    bool found = false;
    coa->getAccount(1500, &acc);
    std::vector<int> subAccountNums = acc->ListHeaderSubAccountNum();

    for(auto accNum: subAccountNums){
        if (accNum == 1600){
            found = true;
        }
    }

    ASSERT_TRUE(found) << "Finding accNum 1600";

    found = false;
    for(auto accNum: subAccountNums){
        if (accNum == 1700){
            found = true;
        }
    }

    ASSERT_FALSE(found) << "Finding accNum 1700";

    found = false;
    for(auto accNum: subAccountNums){
        if (accNum == 1650){
            found = true;
        }
    }

    ASSERT_FALSE(found) << "Finding accNum 1650 (sub acc for 1600)";

}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    std::cout << "Running Tests" << std::endl;
    return RUN_ALL_TESTS();
}