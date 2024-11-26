#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "ColumnMeta.hpp"
#include "Row.hpp"
#include "TableMeta.hpp"

class Table {
public:
    Table(const TableMeta&);
    [[nodiscard]] std::vector<std::shared_ptr<Row> >  getRows() const &&;

    [[nodiscard]] const std::vector<std::shared_ptr<Row> > & getRows() const &;
     TableMeta getTableMeta() const;
private:
    bool insertRow(const std::shared_ptr<Row>& ); // надо дописать обновление табле меты
    friend class TableFactory;
    std::vector< std::shared_ptr<Row> > rows;
    TableMeta columnMetas;
};
