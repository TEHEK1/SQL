#pragma once
#include <memory>
#include <vector>
#include "OrderedIndex.hpp"
#include "Row.hpp"

class OrderedIndex {
public:
    std::vector <std::shared_ptr<Row> > getRange(const Object&, const Object&);
    bool insertRow(std::shared_ptr<Object>, std::shared_ptr<Row>);
    bool deleteRow(std::shared_ptr<Object>);
};
