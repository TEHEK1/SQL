#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "ColumnMeta.hpp"
#include <vector>
#include <string>

TEST(ColumnMeta, getNextIncrement)
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::INT32, {}, 0);

    EXPECT_EQ(*meta.getNextIncrement().get(), Object(ObjectTypes::INT32, 1));
}

TEST(ColumnMeta, canInsert)
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::STRING, {}, 0);
    EXPECT_TRUE(meta.canInsert(std::make_shared<Object>(ObjectTypes::STRING, "22")));
    EXPECT_FALSE(meta.canInsert(std::make_shared<Object>(ObjectTypes::BYTES, std::vector<bool>(10))));
}

TEST(ColumnMeta, canDelete)
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::STRING, {}, 0);
    EXPECT_TRUE(meta.canDelete(std::make_shared<Object>(ObjectTypes::STRING, "22")));
    EXPECT_FALSE(meta.canDelete(std::make_shared<Object>(ObjectTypes::BYTES, std::vector<bool>(10))));
}

TEST(ColumnMeta, canUpdate)
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::BYTES, {}, 0);
    EXPECT_TRUE(meta.canUpdate(std::make_shared<Object>(ObjectTypes::BYTES, std::vector<bool>(10)), std::make_shared<Object>(ObjectTypes::BYTES, std::vector<bool>(10))));
    EXPECT_FALSE(meta.canUpdate(std::make_shared<Object>(ObjectTypes::STRING, "2222"), std::make_shared<Object>(ObjectTypes::STRING, "2222")));
}


TEST(ColumnMeta, getDefaultValue) 
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::INT32, {}, -1, 0, std::make_shared<Object>(ObjectTypes::INT32, 14));
    
    int result = meta.getDefaultValue().get() -> getValue<int>();
    
    EXPECT_EQ(result, 14);
}

TEST(ColumnMeta, hasAutoIncrement) 
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::BYTES, {}, 0);
    EXPECT_FALSE(meta.hasAutoIncrement());
}

TEST(ColumnMeta, hasDefaultValue) 
{
    ColumnMeta meta = ColumnMeta(4, ObjectTypes::INT32, {}, -1, 0, std::make_shared<Object>(ObjectTypes::INT32, 14));
    ColumnMeta meta1 = ColumnMeta(4, ObjectTypes::BYTES, {}, 0);
    EXPECT_TRUE(meta.hasDefaultValue());
    EXPECT_FALSE(meta1.hasDefaultValue());
}