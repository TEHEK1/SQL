#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "Object.hpp"
#include "ObjectTypes.hpp"
#include <vector>
#include <string>
#include <exception>

TEST(DataBase, operation)
{
    Object object1(ObjectTypes::STRING, "a");
    Object object2(ObjectTypes::STRING, "b");
    Object object3(ObjectTypes::STRING, "b");
    Object object4(ObjectTypes::BYTES, {"b"});
    EXPECT_TRUE(object1 < object2);
    EXPECT_FALSE(object1 > object2);
    EXPECT_FALSE(object3 == object4);
}



TEST(DataBase, getValue)
{
    Object object1(ObjectTypes::STRING, "aha");
    Object object2(ObjectTypes::STRING, "bha");
    Object object3(ObjectTypes::STRING, "b");
    Object object4(ObjectTypes::BYTES, {"b"});
    EXPECT_EQ(object3.getValue<std::string>(), "b");
}