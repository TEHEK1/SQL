#pragma once
#include "Operator.hpp"
// Maybe create namespace?
class OperatorMinus : public Operator{
public:
    OperatorMinus(const Operator& operator1, const Operator& operator2);
    Object getObjectOperator(const Row&, const ColumnMeta&) override;
    ~OperatorMinus() override = default;
};
