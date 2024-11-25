#pragma once
#include <string>
#include "Table.hpp"

class JoinEqual {
    JoinEqual(const std::string& , const std::string& );
    std::shared_ptr<Table> execute();
};
