#ifndef DATABASE_H
#define DATABASE_H


#include <sqlite3.h>
#include <string>
#include <vector>

using Record = std::vector<std::string>;
using Records = std::vector<Record>;


class Database {
    private:
    bool connected = false;
    sqlite3* db;
    void setupDatabase();
    static int selectCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names);

    public:
    int connectDatabase(std::string filename);
    int closeDatabase();
    int createDatabase(std::string filename);
    Records query(std::string sql);
    int insert(std::string sql);
    int update(std::string sql);
    // int CreateDatabase();

};

#endif