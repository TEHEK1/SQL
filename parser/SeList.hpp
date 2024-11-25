#pragma once
#include <vector>
#include "Operator.hpp"
#include "Table.hpp"
class SeList {
public:
    explicit SeList(const std::vector<std::shared_ptr<Operator> >& columns);
    std::shared_ptr<Table> execute(const std::shared_ptr<Table>&);
private:
    std::vector<std::shared_ptr<Operator> > m_columns;
};
