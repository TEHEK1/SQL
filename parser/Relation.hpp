#pragma once
#include <memory>
#include "DataBase.hpp"
#include "Table.hpp"

class Relation {
public:
    virtual std::shared_ptr<Table> execute(const std::shared_ptr<DataBase>&) = 0;
    virtual ~Relation() = default;
};
