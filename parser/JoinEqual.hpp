#pragma once
#include <memory>
#include <string>
#include "Table.hpp"
#include "Row.hpp"

class JoinEqual {
public:
    JoinEqual(const std::string& , const std::string& );
    std::shared_ptr<Table> execute(const std::shared_ptr<Row> &, const TableMeta &, const std::shared_ptr<Table> &) const;
private:
    std::string m_columnName1;
    std::string m_columnName2;
};
