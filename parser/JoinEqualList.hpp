#pragma once
#include <vector>
#include "JoinEqual.hpp"
#include "Table.hpp"

class JoinEqualList {
public:
    JoinEqualList(const std::vector<std::shared_ptr<JoinEqual>>&);
    std::shared_ptr<Table> execute(const std::string& tableName1, const std::shared_ptr<Table> & table1,
                  const std::string& tableName2, const std::shared_ptr<Table> & table2 );

private:
    std::vector<std::shared_ptr<JoinEqual>> m_joinEquals;
};
