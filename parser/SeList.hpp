#pragma once
#include <vector>
#include "Operator.hpp"
#include "Table.hpp"
class SeList {
public:
    SeList(std::vector<std::shared_ptr<Operator> > columns);
    std::shared_ptr<Table> execute(std::shared_ptr<Table>);
private:
    std::vector<Operator> m_columns;
};
