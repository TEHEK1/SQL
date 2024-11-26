#include <gtest/gtest.h>  // Include the GoogleTest framework header
#include "RowFactory.hpp"
#include "Row.hpp"
#include <vector>
#include <string>
#include <exception>

TEST(RowFactory, concatenateRow)
{
    std::vector<std::shared_ptr<Object>> f;
    std::vector<std::shared_ptr<Object>> f1;
    std::shared_ptr<Row> row;
    std::shared_ptr<Row> row1;
    std::shared_ptr<Row> row2;

    f.push_back(std::make_shared<Object>(ObjectTypes::STRING, "a"));
    f.push_back(std::make_shared<Object>(ObjectTypes::INT32, 4));
    row = std::make_shared<Row>(f);
    f1.push_back(std::make_shared<Object>(ObjectTypes::STRING, "a"));
    f1.push_back(std::make_shared<Object>(ObjectTypes::BOOL, true));
    row1 = std::make_shared<Row>(f1);
    row2 = RowFactory::concatenateRow(row, row1);
    
    for(int i = 0; i < 4; i++) {
        if(i < 2) {
            EXPECT_EQ(*((row2 -> getField(i)).get()), *((row -> getField(i)).get()));
        } else {
            EXPECT_EQ(*(row2 -> getField(i).get()), *(row1 -> getField(i - 2).get()));
        }
    }
}