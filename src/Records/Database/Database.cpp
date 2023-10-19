#include <Database.h>
#include <iostream>
#include <filesystem>
// #include <pqxx/pqxx>


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

int Database::closeDatabase(){
    if(connected){
        connected = false;
        return sqlite3_close(db);
    } else {
        std::cout << "No database connection" << std::endl;
        return 1;
    }
    
}
