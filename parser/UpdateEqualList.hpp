#pragma once
#include <vector>
#include "UpdateEqual.hpp"
#include "Table.hpp"

class UpdateEqualList {
public:
    UpdateEqualList(const std::vector<UpdateEqual>&);
    Table execute(Table&);
    const std::vector<UpdateEqual>& getUpdateEquals() const;

};