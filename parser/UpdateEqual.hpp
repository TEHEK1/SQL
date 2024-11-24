#pragma once
#include "string"
#include "Operator.hpp"
#include "Table.hpp"
class UpdateEqual {
    UpdateEqual(const std::string&, const Operator&);
    bool execute(const Table&);
};
