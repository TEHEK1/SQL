#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "ColumnMeta.hpp"
#include "Row.hpp"

class Table {
public:
    [[nodiscard]] std::vector<std::shared_ptr<Row> >  getRows() const &&;
    [[nodiscard]] const std::vector<std::shared_ptr<Row> > & getRows() const &;
private:
    //friend class TableFactory;
    std::vector< std::shared_ptr<Row> > rows;
    std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > columnMetas;
};
