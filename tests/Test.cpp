#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "ConditionObject.hpp"
#include "DataBase.hpp"
#include "TableFactory.hpp"
#include "SFW.hpp"
#include "CreateTable.hpp"
#include "InsertToOperatorList.hpp"
#include "DeleteFrom.hpp"
#include "OperatorIdentifier.hpp"
#include "OperatorObject.hpp"
#include "RelationTable.hpp"
#include "Tokenizer.h"
#include "parse_factory/Parser.hpp"
// Dummy test
// Define a test case named 'ExampleTest' and a test named 'test'
TEST(SFW, elementarySFW)
{
    auto dataBase = std::make_shared<DataBase> ();
    auto tableMeta = TableMeta();
    tableMeta.setByName("id", std::make_shared<ColumnMeta>(0, ObjectTypes::BOOL));
    auto table = std::make_shared<Table> (tableMeta);
    dataBase->insertTable("student", table);
    TableFactory::insertRow({{false, std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::BOOL, false))}}, table);
    std::shared_ptr<Query> query =  std::make_shared<SFW>(std::make_shared<SeList>(
            std::vector{std::dynamic_pointer_cast<Operator>(std::make_shared<OperatorIdentifier>("id"))}),
                                                          std::make_shared<RelationTable>("student"),
                                                          std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, true)));
    query->executeQuery(dataBase);

    EXPECT_EQ(true, true);
}

TEST(SFW, stringSFW) {
    auto dataBase = std::make_shared<DataBase> ();
    std::vector<std::string> user_queries ={"CREATE TABLE student ( id: bool )",
                                            "INSERT (true) TO student",
                                            "SELECT id FROM student WHERE true"};
    for(auto user_query : user_queries) {
        auto query = Parser(Tokenizer(user_query)).parse_query(user_query);
        query->executeQuery(dataBase);
        //EXPECT_TRUE(query->executeQuery(dataBase));
    }
}

TEST(CREATE, elementaryCREATE)
{
    auto dataBase = std::make_shared<DataBase> ();
    auto tableMeta = TableMeta();
    tableMeta.setByName("id", std::make_shared<ColumnMeta>(0, ObjectTypes::BOOL));
    auto createTable = std::make_shared<CreateTable>("student", tableMeta);
    EXPECT_TRUE(createTable->executeQuery(dataBase));
    auto insertTo = std::make_shared<InsertToOperatorList>(std::unordered_map<long long, std::shared_ptr<Operator >>{{0, std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::BOOL, false))}} , std::make_shared<RelationTable>("student") );
    EXPECT_TRUE(insertTo->executeQuery(dataBase));
    std::shared_ptr<Query> query =  std::make_shared<SFW>(std::make_shared<SeList>(
                                                                  std::vector{std::dynamic_pointer_cast<Operator>(std::make_shared<OperatorIdentifier>("id"))}),
                                                          std::make_shared<RelationTable>("student"),
                                                          std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, true)));
    EXPECT_TRUE(query->executeQuery(dataBase));
}

TEST(DELETE, elementaryDELETE)
{
    auto dataBase = std::make_shared<DataBase> ();
    auto tableMeta = TableMeta();
    tableMeta.setByName("id", std::make_shared<ColumnMeta>(0, ObjectTypes::BOOL));
    auto createTable = std::make_shared<CreateTable>("student", tableMeta);
    EXPECT_TRUE(createTable->executeQuery(dataBase));
    auto insertTo = std::make_shared<InsertToOperatorList>(std::unordered_map<long long, std::shared_ptr<Operator >>{{0, std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::BOOL, false))}} , std::make_shared<RelationTable>("student") );
    EXPECT_TRUE(insertTo->executeQuery(dataBase));
    auto deleteFrom = std::make_shared<DeleteFrom>(std::make_shared<RelationTable>("student"), std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, true)));
    EXPECT_TRUE(deleteFrom->executeQuery(dataBase));
    std::shared_ptr<Query> query =  std::make_shared<SFW>(std::make_shared<SeList>(
                                                                  std::vector{std::dynamic_pointer_cast<Operator>(std::make_shared<OperatorIdentifier>("id"))}),
                                                          std::make_shared<RelationTable>("student"),
                                                          std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, true)));
    EXPECT_TRUE(query->executeQuery(dataBase));
}

TEST(DELETE, parseDELETE) {
    auto dataBase = std::make_shared<DataBase> ();
    std::vector<std::string> user_queries ={"CREATE TABLE student ( id: bool )",
                                            "INSERT (true) TO student",
                                            "INSERT (false) TO student",
                                            "DELETE student WHERE true",
                                            "SELECT id FROM student WHERE true"};
    for(auto user_query : user_queries) {
        auto query = Parser(Tokenizer(user_query)).parse_query(user_query);
        query->executeQuery(dataBase);
        //EXPECT_TRUE(query->executeQuery(dataBase));
    }
}

int main(int argc, char **argv) {
    // Initialize the GoogleTest framework with command-line arguments
    ::testing::InitGoogleTest(&argc, argv);

    // Run all the tests that have been defined and return the result
    return RUN_ALL_TESTS();
}