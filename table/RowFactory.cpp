#include "RowFactory.hpp"

std::shared_ptr<Row> RowFactory::concatenateRow(const std::shared_ptr<Row>& leftRow, const std::shared_ptr<Row>& rightRow) {
    std::vector<std::shared_ptr<Object>> fields;
    for(auto &i : leftRow -> getFields()) {
        fields.push_back(i);
    }
    for(auto &i : rightRow -> getFields()) {
        fields.push_back(i);
    }
    return std::make_shared<Row>(fields);
}