#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "ObjectFactory.hpp"
#include "Row.hpp"
#include <vector>
#include <string>
#include <exception>

TEST(ObjectFactory, getObjectByColumnName)
{
    TableMeta meta;
    std::shared_ptr<ColumnMeta> mt1 = std::make_shared<ColumnMeta>(0, ObjectTypes::STRING);
    std::shared_ptr<ColumnMeta> mt2 = std::make_shared<ColumnMeta>(1, ObjectTypes::STRING);
    std::vector<std::shared_ptr<Object>> f;
    std::shared_ptr<Row> row;

    f.push_back(std::make_shared<Object>(ObjectTypes::STRING, "a"));
    f.push_back(std::make_shared<Object>(ObjectTypes::STRING, "b"));
    row = std::make_shared<Row>(f);

    meta.setByName("id1", mt1);
    meta.setByName("id2", mt2);
    std::shared_ptr<Object> object = ObjectFactory::getObjectByColumnName("id2", row, meta);
    std::string F = object -> getValue<std::string>();
    EXPECT_EQ(F, "b");
}