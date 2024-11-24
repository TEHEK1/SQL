#pragma once
#include <vector>
#include "Index.hpp"
#include "Row.hpp"

class UnorderedIndex: public Index {
public:
    std::vector <std::shared_ptr<Row> > getEqual(const Object&);
    bool insertRow(std::shared_ptr<Object>, std::shared_ptr<Row>);
    bool deleteRow(std::shared_ptr<Object>);
};
