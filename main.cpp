#include <iostream>
#include <stdio.h>
#include<windows.h>
#include <Database.h>
#include <ChartOfAccounts.h>
#include <sqlite3.h>
#include <vector>
#include <string>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int main(int, char**){
    std::cout.clear();
    std::cout << "Hello, from AccountingManager!"<<std::endl;
    std::cout << "Hello with libpqxx!\n"<<std::endl;
    std::string name = "test.db";
    Database db;
    if (db.createDatabase(name) == 2) {
        db.connectDatabase(name);
    };
    

    
    ChartOfAccounts coa(db);




    coa.CreateAccount(db,1000,"Asset","Asset");
    coa.CreateAccount(db,2000,"Liability","Liability");
    coa.CreateAccount(db,3000,"Equity","Equity");
    coa.CreateAccount(db,4000,"Revenue","Revenue");
    coa.CreateAccount(db,5000,"Exepense","Exepense");
    
    Records records;
    // std::string sql = "SELECT * FROM sqlite_schema WHERE type='table' AND name NOT LIKE 'sqlite_%';";
    // records = db.query(sql);
    // std::cout << "Records Size: " << records.size() << std::endl;
    // for (auto record: records) {
    //     for (auto row: record) std::cout << row << std::endl;
    // }

    std::string sql = "SELECT name FROM sqlite_schema WHERE type='table';";
    int ret = db.query(sql, NULL);
    // std::cout << "Records Size: " << records.size() << std::endl;
    // for (auto record: records) {
    //     for (auto row: record) std::cout << row << std::endl;
    // } 
    
    std::string sql2 = "SELECT * FROM COA ORDER BY ACCNUM;";
    records.clear();
    ret = db.query(sql2, &records);
    std::cout << "ret select all: " << ret << std::endl;
    std::cout << "Records Size: " << records.size() << std::endl;
    for (auto record: records) {
        for (auto row: record) std::cout << row << " ";
        std::cout << std::endl;
    }
    
    db.closeDatabase();
    remove(name.c_str());
    return 0;


}
