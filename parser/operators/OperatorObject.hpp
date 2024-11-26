#pragma once
#include "Operator.hpp"
class OperatorObject : public Operator {
    OperatorObject(const std::shared_ptr<Object>&);
    Object execute(const Row&, const ColumnMeta&) override;
    ~OperatorObject() override = default;
};
