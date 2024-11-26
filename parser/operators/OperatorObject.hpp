#pragma once
#include "Operator.hpp"
class OperatorObject : Operator {
    OperatorObject(const Object&);
    Object getObjectOperator(const Row&, const ColumnMeta&) override;
    ~OperatorObject() override = default;
};
