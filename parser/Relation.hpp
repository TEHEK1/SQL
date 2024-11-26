#pragma once
#include <memory>
#include "DataBase.hpp"
#include "Table.hpp"

class Relation {
public:
    virtual std::shared_ptr<Table> getTableRelation(const std::shared_ptr<DataBase>&) const = 0;
    virtual std::string getName() const = 0;
    virtual ~Relation() = default;
};
