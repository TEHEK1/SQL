#pragma once
#include "Operator.hpp"
// Maybe create namespace?
class OperatorPlus : public Operator{
public:
    OperatorPlus(const Operator& operator1, const Operator& operator2);
    Object getObjectOperator(const Row&, const ColumnMeta&) override;
    ~OperatorPlus() override = default;
};
