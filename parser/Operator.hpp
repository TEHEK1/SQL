#pragma once
#include <memory>
#include "Object.hpp"
#include "Row.hpp"
#include "ColumnMeta.hpp"
class Operator {
public:
    virtual Object execute(const Row&, const ColumnMeta&) = 0;
    virtual ~Operator() = 0;
};
