#pragma once
#include "Table.hpp"

class Condition {
public:
    virtual Table execute (const Table&) = 0;
    virtual ~Condition() = 0;
};
