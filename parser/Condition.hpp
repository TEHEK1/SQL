#pragma once
#include "Table.hpp"

class Condition {
public:
    virtual std::shared_ptr<Table> execute (const std::shared_ptr<Table> &) const = 0;
    virtual ~Condition() = 0;
};
