#include "Table.hpp"
[[nodiscard]] std::vector<std::shared_ptr<Row> >  Table::getRows() const &&
{

    return rows;
}

[[nodiscard]] const std::vector<std::shared_ptr<Row> > & Table::getRows() const &
{
    return rows;
}

TableMeta Table::getTableMeta() const {
    return columnMetas;
}