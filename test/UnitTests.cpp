#include <gtest/gtest.h>
#include <Database.h>
#include <string.h>
#include <vector>
#include <stdio.h>



class DatabaseTest : public ::testing::Test {

    protected:
        Database db;
        std::vector<std::string> databaseNames;
        void TearDown() override {
            db.closeDatabase();
            for (auto name:databaseNames){
                remove(name.c_str());
            }
        }


};

TEST_F(DatabaseTest, DatabaseDoesNotExsistsTest){
    std::string filename = "test.db";
    // databaseNames.push_back(filename);
    ASSERT_EQ(db.connectDatabase(filename),1) << db.connectDatabase(filename) << std::endl;
}

TEST_F(DatabaseTest, DatabaseAlreadyConnectedTest){
    std::string filename = "test.db";
    databaseNames.push_back(filename);
    ASSERT_EQ(db.createDatabase(filename), 0) << "Failed to create Database";
    ASSERT_EQ(db.connectDatabase(filename),-1) << "Trying to connect to the already created database";
}



int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    std::cout << "Running Tests" << std::endl;
    return RUN_ALL_TESTS();
}