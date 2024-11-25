#pragma once
#include <memory>
#include <string>
#include "Table.hpp"
#include "Row.hpp"

class JoinEqual {
    JoinEqual(const std::string& , const std::string& );
    std::shared_ptr<Table> execute(const std::shared_ptr<Row>&, std::shared_ptr<Table>&);
};
