#include <gtest/gtest.h>
#include <sqlite3.h>
#include <Database.h>
#include <string.h>
#include <vector>
#include <stdio.h>



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



int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    std::cout << "Running Tests" << std::endl;
    return RUN_ALL_TESTS();
}