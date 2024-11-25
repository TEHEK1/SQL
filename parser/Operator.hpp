#pragma once
#include <memory>
#include "Object.hpp"
#include "Row.hpp"
#include "ColumnMeta.hpp"
#include "TableMeta.hpp"
class Operator {
public:
    virtual std::shared_ptr<Object> execute(const std::shared_ptr<Row>&, const TableMeta&) = 0;
    virtual ~Operator() = 0;
};
