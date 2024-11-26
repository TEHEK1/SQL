#pragma once
#include <memory>
#include "Object.hpp"
#include "Row.hpp"
#include "ColumnMeta.hpp"
#include "TableMeta.hpp"
class Operator {
public:
    virtual std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row>&, const TableMeta&) const = 0;
    virtual ObjectTypes getTypeOperator(const TableMeta&) const = 0;
    virtual ~Operator() = default;
};
