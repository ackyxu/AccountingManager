#include <Database.h>
#include <iostream>
#include <filesystem>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int Database::connectDatabase(std::string filename) {
    int rc = -1;
    if(std::filesystem::exists(filename) && connected == false) {
        std::cout << "file found" << std::endl;
        rc = sqlite3_open(filename.c_str(), &db);
        connected = true;
        return 0;
    } else if (connected){
        sqlite3_filename filename = sqlite3_db_filename(db, NULL);
        std::cout << "The following database ia already connected:" << filename << std::endl;
        return -1;

    } else {
        std::cout << "file not found, please created a new database" << std::endl;
        return 1;
    } 
}







int Database::createDatabase(std::string filename) {
    if(connected){
        sqlite3_filename filename = sqlite3_db_filename(db, NULL);
        std::cout << "The following database is already connected:" << filename << std::endl;
        std::cout << "Close it first before making a new connection" << std::endl;
        return -1;
    } else if(std::filesystem::exists(filename) == false) {
        int rc = sqlite3_open(filename.c_str(), &db);
        if(rc == SQLITE_OK) {
            Database::setupDatabase();
            std::cout << "database file created: " << filename << std::endl;
            connected = true;
            return 0;
        } else {
            std::cout << "Connection Failed with Code: " << rc << std::endl;
            return 1;
            // Need to figure out how to trigger this for unit test
        }

    } else if(std::filesystem::exists(filename) == true) {
        std::cout << "The database file already exsists" << std::endl;
        return 2;
    }

    return 1;

}


void Database::setupDatabase(){

    std::string sql;
    char* errmsg;

    sql =       "CREATE TABLE COA ("  \
                            "ACCNUM INT PRIMARY KEY     NOT NULL," \
                            "ACCNAME        TEXT        NOT NULL," \
                            "ACCDESC        TEXT        NOT NULL," \
                            "ACCTYPE        INT         NOT NULL," \
                            "ACCGROUP       INT         NOT NULL," \
                            "GRPNUM         INT," \
                            "ACTIVE         INT         NOT NULL);";
                            // "FOREIGN KEY (GRPNUM) REFERENCES COA(ACCNUM)," \


    int ret = sqlite3_exec(db,sql.c_str(),NULL,NULL,&errmsg);
    if (errmsg != NULL){
        std::cout << "Stats Code for Setup:" << errmsg << std::endl;
    }
        

}

int Database::closeDatabase(){
    if(connected){
        connected = false;
        return sqlite3_close(db);
    } else {
        std::cout << "No database connection" << std::endl;
        return 1;
    }
    
}

int Database::selectCallback(void *p_data, int num_fields, char **p_fields, char **p_col_names){
    Records* records = static_cast<Records*>(p_data);

    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...) {
    // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
  return 0;
}

//  https://stackoverflow.com/questions/18839799/retrieve-sqlite-table-data-in-c
int Database::query(std::string sql, Records* records) {
    char* errmsg;
    int ret;
    if(records == NULL) ret = sqlite3_exec(db, sql.c_str(),NULL,NULL,&errmsg);
    else ret = sqlite3_exec(db, sql.c_str(), Database::selectCallback, records, &errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in select statement " << sql << "[" << errmsg << "]\n";
        return 1;
    } else {
        return SQLITE_OK;
    }
}

int Database::insert(std::string sql) {
    char* errmsg;
    int ret = sqlite3_exec(db, sql.c_str(),NULL,NULL,&errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in insert statement " << sql << "[" << errmsg << "]" << std::endl;
    }
    else {
        std::cerr << "Insertion Success" << std::endl;
    }

    return ret;
}


int Database::update(std::string sql) {
    char* errmsg;
    int ret = sqlite3_exec(db, sql.c_str(),NULL,NULL,&errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in update statement " << sql << "[" << errmsg << "]" << std::endl;
    }
    else {
        std::cerr << "Insertion Success" << std::endl;
    }

    return ret;
}


    


