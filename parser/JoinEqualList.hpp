#pragma once
#include <vector>
#include "JoinEqual.hpp"
#include "Table.hpp"

class JoinEqualList {
    JoinEqualList(const std::vector<JoinEqual>&);
    Table execute(const std::string& tableName1, const Table& table1,
                  const std::string& tableName2, const Table& table2 );

};
