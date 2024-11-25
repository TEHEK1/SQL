#pragma once
#include <memory>
#include "Object.hpp"
#include "Operator.hpp"
#include "Row.hpp"
#include "Table.hpp"

class ObjectFactory {
public:
    static std::shared_ptr<Object> getObjectByColumnName(const std::string&, const std::shared_ptr<Row> &, const TableMeta &);
    //static std::shared_ptr<Object> getObjectByNumber(long long, const std::shared_ptr<Row> &, const TableMeta &);
};
