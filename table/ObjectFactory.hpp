#pragma once
#include <memory>
#include "Object.hpp"
#include "Row.hpp"
#include "Table.hpp"

class ObjectFactory {
public:
    static std::shared_ptr<Object> getObjectByColumnName(const std::string&, const std::shared_ptr<Row> &, const TableMeta &);
};
