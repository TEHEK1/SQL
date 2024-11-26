#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "ConditionObject.hpp"
#include "DataBase.hpp"
#include "TableFactory.hpp"
#include "SFW.hpp"
#include "OperatorIdentifier.hpp"
#include "OperatorObject.hpp"
#include "RelationTable.hpp"
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

int main(int argc, char **argv) {
    // Initialize the GoogleTest framework with command-line arguments
    ::testing::InitGoogleTest(&argc, argv);

    // Run all the tests that have been defined and return the result
    return RUN_ALL_TESTS();
}