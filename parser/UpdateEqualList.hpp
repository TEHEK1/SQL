#pragma once
#include <vector>
#include "UpdateEqual.hpp"
#include "Table.hpp"

class UpdateEqualList {
    UpdateEqualList(const std::vector<UpdateEqual>&);
    Table execute(Table&);

};