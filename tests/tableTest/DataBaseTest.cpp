#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "DataBase.hpp"
#include <vector>
#include <string>
#include <exception>

TEST(DataBase, tableOperation)
{
    DataBase data;
    TableMeta meta;
    EXPECT_NO_THROW(data.insertTable("data", std::make_shared<Table>(meta)));
    EXPECT_THROW(data.getTable("222"), std::runtime_error);
    EXPECT_TRUE(data.getTable("data"));
}
