#pragma once
#include <memory>
#include <string>
#include "Operator.hpp"
#include "Table.hpp"
class UpdateEqual {
public:
    UpdateEqual(const std::string&, const std::shared_ptr<Operator>&);
    bool execute(std::shared_ptr<Row> &, const std::shared_ptr<TableMeta>&) const;
private:
    std::string m_columnName;
    std::shared_ptr<Operator> m_resultOperator;
};
