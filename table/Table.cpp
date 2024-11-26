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
TableMeta &Table::getTableMeta() {
    return columnMetas;
}

bool Table::insertRow(const std::shared_ptr<Row>& row) { 
    rows.push_back(row);
    return true;
}

Table::Table(const TableMeta& meta) : columnMetas(meta){}


