#include <sqlite3.h>
#include <string>
class Database {
    private:
    bool connected = false;
    sqlite3* db;

    public:
    int connectDatabase(std::string filename);
    int closeDatabase();
    int createDatabase(std::string filename);
    // int CreateDatabase();

};