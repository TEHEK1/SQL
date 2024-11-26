#include "ObjectFactory.hpp"

std::shared_ptr<Object> ObjectFactory::getObjectByColumnName(const std::string& columnName, const std::shared_ptr<Row> &row, const TableMeta &meta) {
    return row -> getField(meta.getByName(columnName) -> getRealColumnNum());
}
